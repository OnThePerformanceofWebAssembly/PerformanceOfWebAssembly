run:
	node sortcircle_runJS_MEDIUM.js

raplserver:
	$(MAKE) -C Results raplserver

raplclient:
	$(MAKE) -C Results raplclient

localhost:
	python3 -m http.server 8000

googlechrome:
	google-chrome http://localhost:8000/example_runJS_MEDIUM.html -incognito

mozillafirefox:
	firefox -private http://localhost:8000/example_runJS_MEDIUM.html

microsoftedge:
	microsoft-edge -inprivate  http://localhost:8000/example_runJS_MEDIUM.html