set(LIBMISC_SOURCE
        misc.c
        )

add_library(libmisc ${LIBMISC_SOURCE})
set_target_properties(libmisc PROPERTIES OUTPUT_NAME "misc")
