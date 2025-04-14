
/**
 * \file util_DevDebug.h
 * \brief Debugging helper file for asserts and trace.
 * The following macro switches to be set in CMakeLists.txt:
 *
 * DD_ASSERT_EN,
 * DD_TRACE_EN.
 *
 * These macros enable and disable various debug options.
 *
 */

#ifndef UTIL_DEVDEBUG_H__
#define UTIL_DEVDEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

#define __FUNC__                                                               \
    __func__ /*lint !e9071 yes we do intend to use the compiler macro here */

/*lint -elibmacro(9026)*/
/*lint ++flb*/
/**
 * macro for the print function to use
 **/
#if DD_TRACE_EN || DD_ASSERT_EN
    #include <stdio.h>
#endif /* DD_TRACE_EN || DD_ASSERT_EN */

#if DD_TRACE_EN || DD_ASSERT_EN

    #define DD_PRINTF(...) printf(__VA_ARGS__)

    /**
	 * \brief colour output
	 * "\x1B[<Fg colour>;<Bg colour>m<TEXT>\x1B[<reset format attr>m"
	 **/
    #define DD_COL_RESET "\x1B[0m"
    /** \note red & green are used by gtest */
    /* Foreground colours: black, red, green, yellow, blue, magenta, Cyan, White*/
    #define DD_COLOUR_BLK "\x1B[30m]"
    #define DD_COLOUR_RED "\x1B[31m"
    #define DD_COLOUR_GRN "\x1B[32m"
    #define DD_COLOUR_YEL "\x1B[33m"
    #define DD_COLOUR_BLU "\x1B[34m"
    #define DD_COLOUR_MAG "\x1B[35m"
    #define DD_COLOUR_CYN "\x1B[36m"
    #define DD_COLOUR_WHI "\x1B[37m"

    /* Background colours: black, red, green, yellow, blue, magenta, Cyan, White*/
    #define DD_COL_BG_BLK "\x1b[40m"
    #define DD_COL_BG_RED "\x1b[41m"
    #define DD_COL_BG_GRN "\x1b[42m"
    #define DD_COL_BG_YEL "\x1b[43m"
    #define DD_COL_BG_BLU "\x1b[44m"
    #define DD_COL_BG_MAG "\x1b[45m"
    #define DD_COL_BG_CYN "\x1b[46m"
    #define DD_COL_BG_WHI "\x1b[47m"

    #define DD_COLR_ASSERT "\x1B[37;41m"
#else
    #define DD_PRINTF(...) ((void)0)
#endif /* DD_TRACE_EN || DD_ASSERT_EN */

#if DD_TRACE_EN
    #define DD_TRACE(...) DD_PRINTF(__VA_ARGS__)
    #if DD_COLOURIT_TRACE
        #define DD_COL_TRACE(colour, ...)                                      \
            do {                                                               \
                DD_PRINTF(colour);                                             \
                DD_PRINTF(__VA_ARGS__);                                        \
                DD_PRINTF(DD_COL_RESET);                                       \
            } while ( false )
    #else
        #define DD_COL_TRACE(colour, ...) DD_PRINTF(__VA_ARGS__)
    #endif /* DD_COLOURIT_TRACE */
    #define DD_TRACE_ROUTE()                                                   \
        do {                                                                   \
            DD_TRACE("+ %s() L:%d\n", __FUNC__, __LINE__);                     \
        } while ( false )
#else

    #define DD_TRACE(...)             ((void)0)
    #define DD_COL_TRACE(colour, ...) ((void)0)
    #define DD_TRACE_ROUTE()          ((void)0)
#endif /* DD_TRACE_EN */

/**
 * macro to define our own version of assert that does no evil
 **/
#if DD_ASSERT_EN
    #define DD_ASSERT(bCondition)                                              \
        do {                                                                   \
            if ( bCondition ) {                                                \
            } else {                                                           \
                DD_COL_TRACE(                                                  \
                    DD_COLR_ASSERT,                                            \
                    "\nASSERTION FAILED in: %s(), L:%d, A:(%s)%s\n\n",         \
                    __FUNC__, __LINE__, #bCondition, DD_COL_RESET);            \
            }                                                                  \
        } while ( false )
#else
    #define DD_ASSERT(bCondition) ((void)0) /*lint -esym( 714, bCondition ) */

#endif /* DD_ASSERT_EN */


/*lint --flb*/
#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* UTIL_DEVDEBUG_H__ */
