run:
	node example_runWASM_LARGE.js

raplserver:
	$(MAKE) -C Results raplserver

raplclient:
	$(MAKE) -C Results raplclient

localhost:
	python3 -m http.server 8000

googlechrome:
	google-chrome http://localhost:8000/example_runWASM_LARGE.html -incognito

mozillafirefox:
	firefox -private http://localhost:8000/example_runWASM_LARGE.html

microsoftedge:
	microsoft-edge -inprivate  http://localhost:8000/example_runWASM_LARGE.html