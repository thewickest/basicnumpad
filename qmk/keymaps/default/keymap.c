// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum {
    TD_NUM_BLOQ,
};

enum custom_keycodes {
    CALC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │TG1│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │   0   │ . │   │
     * └───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_5x4(
        TD(TD_NUM_BLOQ), KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,   KC_PDOT,          KC_PENT
    ),

        /*
     * ┌───┬───┬───┬───┐
     * │TG1│ / │ * │ - │
     * ┌───┬───┬───┐───┤
     * │Hom│ ↑ │PgU│   │
     * ├───┼───┼───┤ + │
     * │ ← │PrS│ → │   │ - Print Screen
     * ├───┼───┼───┤───┤
     * │End│ ↓ │PgD│   │
     * ├───┴───┼───┤Ent│
     * │Insert │Del│   │
     * └───────┴───┘───┘
     */
    [1] = LAYOUT_numpad_5x4(
        _______, _______, _______, _______,
        KC_HOME, KC_UP,   KC_PGUP,
        KC_LEFT, KC_PSCR, KC_RGHT, _______,
        KC_END,  KC_DOWN, KC_PGDN,
        KC_INS,           KC_DEL,  _______
    ),

    /* Media Keys
     * ┌───┬───┬───┬───┐
     * │TG1│   │   │   │
     * ┌───┬───┬───┐───┤
     * │   │VUp│   │   │ - Volume Up
     * ├───┼───┼───┤   │ 
     * │Prv│Pse│Nxt│   │ - Previous Track, Pause, Next Track
     * ├───┼───┼───┤───┤ 
     * │   │VDo│   │   │ - Volumne Down
     * ├───┴───┼───┤   │ 
     * |Mte│   │   │   | - Mute
     * └───────┴───┘───┘
     */
    [2] = LAYOUT_numpad_5x4(
        _______, _______, _______, _______,
        XXXXXXX, KC_VOLU, XXXXXXX,
        KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
        XXXXXXX, KC_VOLD, XXXXXXX,
        KC_MUTE,          XXXXXXX, XXXXXXX
    ),

        /* Media Keys
     * ┌───┬───┬───┬───┐
     * │   │   │   │   │
     * ┌───┬───┬───┐───┤
     * │F13│F14│F15│   │
     * ├───┼───┼───┤   │ 
     * │F16│F17│F18│   |
     * ├───┼───┼───┤───┤ 
     * │F19│F20│F21│   │
     * ├───┴───┼───┤   │ 
     * |Rst│   │   │   | - Put the keyboard in Boot mode
     * └───────┴───┘───┘
     */
    [3] = LAYOUT_numpad_5x4(
        _______, _______, _______, _______,
        CALC,  KC_F14,  KC_F15,
        KC_F16,  KC_F17,  KC_F18,   XXXXXXX,
        KC_F19,  KC_F20,  KC_F21,
        QK_BOOT,          XXXXXXX, XXXXXXX
    )
};

// SPOTIFY, VS_CODE,  KI_KAD, XXXXXXX,


// Functions that control what our tap dance key does
void switch_layer(tap_dance_state_t *state, void *user_data) {
    //ql_tap_state.state = cur_dance(state);
    switch (state->count) {
        case 1:
            layer_move(0);
            break;
        case 2:
            layer_move(1);
            break;
        case 3:
            layer_move(2);
            break;
        case 4:
            layer_move(3);
            break;
        default:
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CALC:
            if(record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_R) SS_UP(X_LGUI) SS_DELAY(50) "calc" SS_TAP(X_ENTER));
            } else {
                //
            }
            break;
    }
    return true;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_NUM_BLOQ] = ACTION_TAP_DANCE_FN(switch_layer)
};