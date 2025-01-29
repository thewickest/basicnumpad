// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum {
    TD_NUM_BLOQ,
};

enum custom_keycodes {
    SPOTIFY = SAFE_RANGE,
    VS_CODE,
    KI_KAD,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SPOTIFY:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LGUI("R")"spotify");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case VS_CODE:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LGUI("R")"code");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case KI_KAD:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LGUI("R")"D:\\Program Files\\KiCad\\7.0\\bin\\kikad.exe");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    default:
        break;
    }
    return true;
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
     * │ ← │   │ → │   │
     * ├───┼───┼───┤───┤
     * │End│ ↓ │PgD│   │
     * ├───┴───┼───┤Ent│
     * │Insert │Del│   │
     * └───────┴───┘───┘
     */
    [1] = LAYOUT_numpad_5x4(
        _______, _______, _______, _______,
        KC_HOME, KC_UP,   KC_PGUP,
        KC_LEFT, XXXXXXX, KC_RGHT, _______,
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
     * │   │   │   │   │
     * ├───┼───┼───┤   │ 
     * │   │   │   │   │
     * ├───┼───┼───┤───┤ 
     * │   │   │   │   │
     * ├───┴───┼───┤   │ 
     * |Rst│   │   │   | - Put the keyboard in Boot mode
     * └───────┴───┘───┘
     */
    [3] = LAYOUT_numpad_5x4(
        _______, _______, _______, _______,
        XXXXXXX, XXXXXXX, XXXXXXX,
        SPOTIFY, VS_CODE, KI_KAD, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
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

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_NUM_BLOQ] = ACTION_TAP_DANCE_FN(switch_layer)
};