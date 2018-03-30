PORT=8888

all:
    npm install
    cors-server $(PORT)
    cd src/python
    python app.py