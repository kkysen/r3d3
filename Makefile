PORT = 8888

all:
	npm install
	cors-server $(PORT)
	touch running
	cd src/python
	python app.py