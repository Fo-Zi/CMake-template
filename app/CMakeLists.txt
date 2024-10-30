### This will be done only if unit testing is enabled, and done through the host's compiler, not the cross-compile one
if( !(UTESTS_BUILD STREQUAL "HOST") )

	## Compile for target here

endif()