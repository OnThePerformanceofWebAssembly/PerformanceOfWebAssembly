raplserver:
	sudo modprobe msr
	sudo ../../../../../RAPL/raplServer

raplclient:
	sudo modprobe msr
	xdg-settings set default-web-browser microsoft-edge-beta.desktop
	for number in 1 2 3 4 5; do \
		sleep 3;sudo ../../../../../RAPL/raplClient 10000 hp20$$number "sudo -u diguest microsoft-edge -inprivate  http://localhost:3000/?disableWebAssembly=true";\
    done