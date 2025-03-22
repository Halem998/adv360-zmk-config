#pragma once

// Utility macros for string manipulation (if needed)
#define ZMK_HELPER_STRINGIFY(x) #x

// Unicode input method definitions
#if !defined OS_UNICODE_LEAD
    #define OS_UNICODE_LEAD &macro_press &kp LALT  // macOS Unicode input
#endif

#if !defined OS_UNICODE_TRAIL
    #define OS_UNICODE_TRAIL &macro_release &kp LALT
#endif

// Macro for creating Unicode input sequences
#define UC_MACRO(name, unicode_bindings) \
    / { \
        macros { \
            name: name { \
                compatible = "zmk,behavior-macro"; \
                #binding-cells = <0>; \
                bindings = <OS_UNICODE_LEAD>, <&macro_tap unicode_bindings>, <OS_UNICODE_TRAIL>; \
            }; \
        }; \
    };

// Macro for creating shifted/unshifted Unicode pairs
#define ZMK_UNICODE_PAIR(name, L0, L1, L2, L3, U0, U1, U2, U3) \
    UC_MACRO(name ## _lower, &kp L0 &kp L1 &kp L2 &kp L3) \
    UC_MACRO(name ## _upper, &kp U0 &kp U1 &kp U2 &kp U3) \
    / { \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                #binding-cells = <0>; \
                bindings = <&name ## _lower>, <&name ## _upper>; \
                mods = <(MOD_LSFT|MOD_RSFT)>; \
            }; \
        }; \
    };
