#include (BundleUtilities)
#fixup_bundle(${CMAKE_INSTALL_PREFIX}/scidavis.app "" "")
# the old way causes a crash with scidavis runs, the fix_bundle method fails to run
#execute_process(COMMAND sh packaging/mkMacDist.sh ${CMAKE_INSTALL_PREFIX}/scidavis.app)
