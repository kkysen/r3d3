//
// Created by Khyber on 4/2/2018.
//

#include "DsvMissingDataStats.h"

#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>

//#include "utils.h"

#define likely(x)    __builtin_expect (!!(x), 1)
#define unlikely(x)  __builtin_expect (!!(x), 0)

#define p(x) std::cout << #x << ": " << (x) << std::endl

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> vector) {
    out << "[";
    auto size = vector.size();
    if (size == 0) {
        return out << "]";
    }
    for (auto i = 0;; i++) {
        out << vector[i];
        if (i == size - 1) {
            return out << "]";
        }
        out << ", ";
    }
}

template<typename Value, typename Total, typename Percent=double>
std::vector<Percent> calcPercents(const std::vector<Value> values, const Total total) {
    const size_t size = values.size();
    std::vector<Percent> percents(size);
    for (size_t i = 0; i < size; i++) {
        percents[i] = (Percent) values[i] / (Percent) total;
    }
    return percents;
};

DsvMissingDataStats::Axis::Axis(const DsvMissingDataStats::Axis::Args args) noexcept :
        ignoredIndices(args.ignoredIndices),
        ignored(args.ignored),
        size(args.size),
        counts(args.counts),
        percents(args.percents) {
    
}

DsvMissingDataStats::Columns::Columns(const DsvMissingDataStats::Axis::Args args,
                                      const std::vector<std::string> columns) noexcept :
        Axis(args), values(columns) {
    
}

DsvMissingDataStats::Rows::Rows(const DsvMissingDataStats::Axis::Args args) noexcept : Axis(args) {}

DsvMissingDataStats::DsvMissingDataStats(const Args args) noexcept :
        dataLocation(args.dataLocation),
        columns(Columns(args.columnArgs, args.columns)),
        rows(Rows(args.rowArgs)) {
    
}

template<char delimiter>
size_t countDelimiter(const std::string s) noexcept {
    return static_cast<size_t>(std::count(s.begin(), s.end(), delimiter));
}

template<char delimeter>
std::vector<std::string> split(const std::string s, const size_t numTokens) noexcept {
    size_t prev = 0;
    size_t pos = 0;
    std::vector<std::string> tokens;
    tokens.reserve(numTokens);
    for (auto i = 0; i < numTokens - 1; i++) {
        pos = s.find(delimeter, prev);
        tokens.push_back(s.substr(prev, pos - prev));
        prev = pos + sizeof(delimeter);
    }
    tokens.push_back(s.substr(prev, s.length()));
    return tokens;
}

template<typename T>
void checkValuesInRange(const std::vector<T> values, T min, T max) {
    std::stringstream msg("Out of Range: ");
    for (const T t : values) {
        if (t < min) {
            msg << t << " < " << min;
            throw new std::out_of_range(msg.str());
        }
        if (t > max) {
            msg << t << " > " << min;
            throw new std::out_of_range(msg.str());
        }
    }
}

template<typename T>
std::vector<bool> indicesToBitSet(const std::vector<T> indices, const T size) noexcept {
    std::vector<bool> bitSet(size);
    for (const T t : indices) {
        bitSet[t] = true;
    }
    return bitSet;
}

template<typename T>
std::vector<bool> indicesToBitSetChecked(const std::vector<T> indices, const T size) {
    checkValuesInRange(indices, (T) 0, size);
    std::vector<bool> bitSet(size);
    for (const T t : indices) {
        bitSet[t] = true;
    }
    return bitSet;
}

DsvMissingDataStats::Axis::Args DsvMissingDataStats::Axis::defaultArgs(std::vector<size_t> ignoredIndices) noexcept {
    return {
            .ignoredIndices = ignoredIndices,
            .ignored = std::vector<bool>(),
            .size = 0,
            .counts = std::vector<size_t>(),
            .percents = std::vector<double>(),
    };
}

DsvMissingDataStats::Args DsvMissingDataStats::defaultArgs(
        std::string dataLocation,
        std::vector<size_t> ignoredColumnIndices, std::vector<size_t> ignoredRowIndices) noexcept {
    return {
            .dataLocation = dataLocation,
            .columnArgs = DsvMissingDataStats::Axis::defaultArgs(ignoredColumnIndices),
            .rowArgs = DsvMissingDataStats::Axis::defaultArgs(ignoredRowIndices),
            .columns = std::vector<std::string>(),
    };
}

DsvMissingDataStats::FileArgs::FileArgs(std::string path, std::vector<size_t> ignoredColumns,
                                        std::vector<size_t> ignoredRows) :
        path(path),
        ignoredColumns(ignoredColumns),
        ignoredRows(ignoredRows) {
    p(ignoredColumns);
    p(ignoredRows);
}

template<char delimiter>
DsvMissingDataStats DsvMissingDataStats::ofFile(const FileArgs args) {
    const std::string path = args.path;
    const std::vector<size_t> ignoredColumnIndices = args.ignoredColumns;
    const std::vector<size_t> ignoredRowIndices = args.ignoredRows;
    
    std::ifstream file(path);
    if (!file) {
        throw std::ifstream::failure(path);
    }
    
    std::string columnLine;
    std::getline(file, columnLine);
    const size_t numColumns = countDelimiter<delimiter>(columnLine) + 1;
    if (numColumns == 0) {
        return DsvMissingDataStats(defaultArgs(path, ignoredColumnIndices, ignoredRowIndices));
    }
    
    const auto ignoredColumns = indicesToBitSetChecked(ignoredColumnIndices, numColumns);
    const auto ignoredRows = indicesToBitSetChecked(ignoredRowIndices, numColumns);
    
    const auto columns = split<delimiter>(columnLine, numColumns);
    size_t* columnCounts = new size_t[numColumns](); // init to 0
    size_t* rowCounts = new size_t[numColumns](); // init to 0
    
    size_t i = 0;
    for (std::string line; std::getline(file, line); i++) {
        bool prevDelim = true;
        size_t numEmptyDelims = 0;
        size_t delimNum = 0;
        for (size_t j = 0; j < line.length(); j++) {
            const bool isDelim = line[j] == delimiter;
            if (isDelim) {
                if (prevDelim && !ignoredColumns[delimNum]) {
                    columnCounts[delimNum]++;
                    numEmptyDelims++;
                }
                delimNum++;
            }
            prevDelim = isDelim;
        }
        if (prevDelim && !ignoredColumns[delimNum]) {
            // with EOL as terminator
            columnCounts[delimNum]++;
            numEmptyDelims++;
        }
        const size_t numColsInRow = numColumns - (numEmptyDelims + 1);
        if (likely(numColsInRow < numColumns) && !ignoredRows[numColsInRow]) {
            rowCounts[numColsInRow]++;
        } else {
            std::cerr << "bad line " << i + 1 << std::endl;
        }
    }
    const size_t numRows = i;
    
    auto columnCountsVector = std::vector<size_t>(columnCounts, columnCounts + numColumns);
    auto rowCountsVector = std::vector<size_t>(rowCounts, rowCounts + numColumns);
    return DsvMissingDataStats(
            {
                    .dataLocation = path,
                    .columnArgs = {
                            .ignoredIndices = ignoredColumnIndices,
                            .ignored = ignoredColumns,
                            .size = numColumns,
                            .counts = columnCountsVector,
                            .percents = calcPercents(columnCountsVector, numRows),
                    },
                    .rowArgs = {
                            .ignoredIndices = ignoredRowIndices,
                            .ignored = ignoredRows,
                            .size = numRows,
                            .counts = rowCountsVector,
                            .percents = calcPercents(rowCountsVector, numRows),
                    },
                    .columns = columns,
            }
    );
}

DsvMissingDataStats DsvMissingDataStats::ofCsvFile(const FileArgs args) {
    return ofFile<','>(args);
}

DsvMissingDataStats DsvMissingDataStats::ofTsvFile(const FileArgs args) {
    return ofFile<'\t'>(args);
}

void DsvMissingDataStats::Columns::appendName(std::stringstream& ss, size_t i, std::string column) const noexcept {
    ss << "Column " << i << ": " << column;
}

void DsvMissingDataStats::Rows::appendName(std::stringstream& ss, size_t i, std::string column) const noexcept {
    ss << i << " Entries";
}

static const std::string TAB = "    ";

void DsvMissingDataStats::Axis::append(
        std::stringstream& ss, const std::string heading, const DsvMissingDataStats& stats) const noexcept {
    ss << "\n" << heading << " (" << stats.columns.ignoredIndices.size() << " ignored):\n";
    
    const std::vector<std::string> columns = stats.columns.values;
    const size_t numColumns = columns.size();
    for (size_t i = 0; i < numColumns; i++) {
        ss << TAB;
        appendName(ss, i + 1, columns[i]);
        ss << ": ";
        if (ignored[i]) {
            ss << "ignored";
        } else {
            ss << counts[i] << " (" << percents[i] * 100 << "%)";
        }
        ss << "\n";
    }
}

std::string DsvMissingDataStats::toString() const noexcept {
    const std::string title = "Missing Data Stats: " + dataLocation;
    if (columns.size == 0) {
        return title + ": " + "no data";
    }
    
    std::stringstream ss;
    ss << title << ": (" << columns.size << " x " << rows.size << ")\n";
    
    ss << TAB << "ignoredColumns: " << columns.ignoredIndices << "\n";
    ss << TAB << "ignoredRows: " << rows.ignoredIndices << "\n";
    
    columns.append(ss, "Data Missing in Each Column", *this);
    rows.append(ss, "Number of Rows with Number of Complete Entries", *this);
    
    return ss.str();
}
