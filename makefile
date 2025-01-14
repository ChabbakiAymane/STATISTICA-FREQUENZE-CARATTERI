help :
	@echo TODO -- Supply help
	cat README

.PHONY : build
build : 
	@echo TODO -- Build
	$(MAKE) build -C ./src

.PHONY : clean
clean : 
	@echo TODO -- Clean
	$(MAKE) clean -C ./src
	rm -r bin