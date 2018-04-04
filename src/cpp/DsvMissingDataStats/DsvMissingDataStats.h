//
// Created by Khyber on 4/2/2018.
//

#ifndef DSVMISSINGDATASTATS_DSVMISSINGDATASTATS_H
#define DSVMISSINGDATASTATS_DSVMISSINGDATASTATS_H

// TODO when columns are ignored, rowCounts need to be adjusted

#include <cstddef>
#include <string>
#include <vector>

class DsvMissingDataStats {

public:
    
    class Axis {
        
        friend class DsvMissingDataStats;
    
    public:
        
        const std::vector<size_t> ignoredIndices;
        const std::vector<bool> ignored;
        const size_t size;
        const std::vector<size_t> counts;
        const std::vector<double> percents;
    
    private:
        
        void append(std::stringstream& ss, std::string heading, const DsvMissingDataStats& stats) const noexcept;
        
        virtual void appendName(std::stringstream& ss, size_t i, std::string column) const noexcept = 0;
        
        struct Args {
            std::vector<size_t> ignoredIndices;
            std::vector<bool> ignored;
            size_t size;
            std::vector<size_t> counts;
            std::vector<double> percents;
        };
        
        static Args defaultArgs(std::vector<size_t> ignoredIndices) noexcept;
        
        explicit Axis(Args args) noexcept;
        
    };
    
    class Columns : public Axis {
        
        friend class DsvMissingDataStats;
    
    public:
        
        const std::vector<std::string> values;
    
    private:
        
        Columns(Args args, std::vector<std::string> columns) noexcept;
        
        void appendName(std::stringstream& ss, size_t i, std::string column) const noexcept final;
        
    };
    
    class Rows : public Axis {
        
        friend class DsvMissingDataStats;
    
    private:
        
        explicit Rows(Args args) noexcept;
        
        void appendName(std::stringstream& ss, size_t i, std::string column) const noexcept final;
        
    };
    
    const std::string dataLocation;
    
    const Columns columns;
    const Rows rows;
    
    std::string toString() const noexcept;
    
    class FileArgs {
    
    public:
        
        std::string path;
        std::vector<size_t> ignoredColumns;
        std::vector<size_t> ignoredRows;
        
        explicit FileArgs(std::string path,
                          std::vector<size_t> ignoredColumns = std::vector<size_t>(),
                          std::vector<size_t> ignoredRows = std::vector<size_t>());
        
    };
    
    template<char delimiter>
    static DsvMissingDataStats ofFile(FileArgs args);
    
    static DsvMissingDataStats ofCsvFile(FileArgs args);
    
    static DsvMissingDataStats ofTsvFile(FileArgs args);

private:
    
    struct Args {
        std::string dataLocation;
        
        Columns::Args columnArgs;
        Rows::Args rowArgs;
        std::vector<std::string> columns;
    };
    
    static Args defaultArgs(std::string dataLocation,
                            std::vector<size_t> ignoredColumnIndices,
                            std::vector<size_t> ignoredRowIndices) noexcept;
    
    explicit DsvMissingDataStats(Args args) noexcept;
    
};

#endif //DSVMISSINGDATASTATS_DSVMISSINGDATASTATS_H
