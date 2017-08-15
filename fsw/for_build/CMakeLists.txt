
add_airliner_app_def(hs
    FILE HS
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_monitors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_monitors.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_msgdefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_tbl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_verify.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(hs-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_custom_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_custom_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_monitors_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_monitors_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hs_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_monitors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_monitors.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_msgdefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_tbl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_verify.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hs_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)

