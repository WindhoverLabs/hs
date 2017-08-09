
add_airliner_app_def(hs
    FILE HS
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_monitors.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(hs-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_custom_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_monitors_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_monitors.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)

