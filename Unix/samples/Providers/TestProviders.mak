TEST_PROVIDER_DIRS = \
	Perf_WMIv2 \
	TestClass_AllDMTFArrays \
	TestClass_AllDMTFTypes \
	TestClass_Employee \
	TestClass_MethodProvider_Calc \
	Test_AssociationProvider \
	Test_TorSwitchSchema \
	Test_Indication \
#	Test_BigProvider \
#	Test_Perf_WMIv2_SingleThread \
#	TestClass_ComplexGraphs \

testproviders:
	for DIR in $(TEST_PROVIDER_DIRS); do \
		if test $$DIR = Test_Indication; then \
			$(MAKE) dep -C $$DIR; \
		fi; \
		$(MAKE) -C $$DIR; \
	done \

regtestproviders:
	for DIR in $(TEST_PROVIDER_DIRS); do \
		$(MAKE) regtest -C $$DIR; \
	done \

cleantestproviders:
	for DIR in $(TEST_PROVIDER_DIRS); do \
		$(MAKE) clean -C $$DIR; \
	done \