/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

// LAYERS
enum custom_user_layers {
    _BASE,
    _FN1,
    _VIM,
};

const uint8_t LAYER_COUNT = 3;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_SLEP, KC_INS,          _______,
        _______, RM_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RM_VALU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, RM_VALD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RM_HUEU, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RM_NEXT, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),

    [_VIM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, MO(_FN1), _______, _______, _______, _______
    ),

};

// LAYER HANDLING
uint8_t selected_layer = 0;

uint8_t get_selected_layer(void) {
    return selected_layer;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t mods_state = get_mods();
    if (mods_state & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, encoder changes layers
        if (clockwise) {
            if(selected_layer  < (LAYER_COUNT - 1)) {
                selected_layer ++;
                layer_move(selected_layer);
            }
        } else {
            if (selected_layer  > 0) {
                selected_layer --;
                layer_move(selected_layer);
            }
        }
    } else if (mods_state & MOD_BIT(KC_RCTL)) {  // if holding Right Ctrl, change rgb hue/colour
        if (clockwise) {
            rgb_matrix_increase_hue_noeeprom();
        } else {
            rgb_matrix_decrease_hue_noeeprom();
        }
    } else if (mods_state & MOD_BIT(KC_RALT)) { // if holding Right Alt, change rgb saturation
        if (clockwise) {
            rgb_matrix_increase_sat_noeeprom();
        } else {
            rgb_matrix_decrease_sat_noeeprom();
        }
    } else if (mods_state & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next/prev track
        if (clockwise) {
            tap_code(KC_MEDIA_NEXT_TRACK);
        } else {
            tap_code(KC_MEDIA_PREV_TRACK);
        }
    } else  { // Otherwise it just changes volume
        if (clockwise) { 
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }

    return false;
}

// Capslock, Scroll lock and Numlock  indicator on Left side lights.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    led_t led_state = host_keyboard_led_state();
    if (led_state.scroll_lock) {
        rgb_matrix_set_color(LED_L1, RGB_GREEN);
        rgb_matrix_set_color(LED_L2, RGB_GREEN);
    }

    #ifdef INVERT_NUMLOCK_INDICATOR
        if (!led_state.num_lock) {   // on if NUM lock is OFF
            rgb_matrix_set_color(LED_L3, RGB_MAGENTA);
            rgb_matrix_set_color(LED_L4, RGB_MAGENTA);
        }
    #else
        if (led_state.num_lock) {   // Normal, on if NUM lock is ON
            rgb_matrix_set_color(LED_L3, RGB_MAGENTA);
            rgb_matrix_set_color(LED_L4, RGB_MAGENTA);
        }
    #endif // INVERT_NUMLOCK_INDICATOR

    if (led_state.caps_lock) {
        rgb_matrix_set_color(LED_L5, RGB_RED);
        rgb_matrix_set_color(LED_L6, RGB_RED);
        rgb_matrix_set_color(LED_L7, RGB_RED);
    }

    if (keymap_config.no_gui) {
        rgb_matrix_set_color(LED_LWIN, RGB_RED);  //light up Win key when disabled
    }

    switch(get_highest_layer(layer_state)){  // special handling per layer
        case _FN1:  // on Fn layer select what the encoder does when pressed
            rgb_matrix_set_color(LED_F5, RGB_RED);
            rgb_matrix_set_color(LED_F6, RGB_RED);
            rgb_matrix_set_color(LED_F7, RGB_RED);
            rgb_matrix_set_color(LED_F8, RGB_RED);
            rgb_matrix_set_color(LED_FN, RGB_RED); //FN key
        case _VIM:
            rgb_matrix_set_color(LED_H, RGB_GREEN);
            rgb_matrix_set_color(LED_J, RGB_GREEN);
            rgb_matrix_set_color(LED_K, RGB_GREEN);
            rgb_matrix_set_color(LED_L, RGB_GREEN);
            rgb_matrix_set_color(LED_CAPS, RGB_GREEN);
        default:
            break;
    }

    return true;
}

// #if defined(ENCODER_MAP_ENABLE)
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//     [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
//     [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
// };
// #endif
