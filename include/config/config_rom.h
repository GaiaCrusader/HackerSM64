#pragma once

/****************
 * ROM SETTINGS *
 ****************/

/**
 * Internal ROM name. NEEDS TO BE **EXACTLY** 20 CHARACTERS. Can't be 19 characters, can't be 21 characters. You can fill it with spaces.
 * The end quote should be here:               "
 */
#define INTERNAL_ROM_NAME "SUPER MARIO 128     "

/**
 * Force the game to delete any existing save data originating from a different hack. This requires INTERNAL_ROM_NAME to be unique to work properly.
 * It is recommended to enable this if any significant changes to the save file are made that could cause issues with this or other hacks.
 * NOTE: Using save editors with this define will likely just end up wiping your save, since SM64 specific save editors most likely use hardcoded save magic.
 */
// #define UNIQUE_SAVE_DATA

/**
 * Enables Rumble Pak Support.
 */
#define ENABLE_RUMBLE

/**
 * The maximum number of supported players/controllers. 1-4.
 * This will save performance if the player has extra unused controllers plugged in.
 * NOTE: Default is 1, maximum is 4.
 * NOTE: If this is 1, the first controller with input after boot will become player 1. Otherwise, player numbers are automatically assigned via port order.
 * NOTE: It is highly recommended to enable ENABLE_STATUS_REPOLLING_GUI if this is greater than 1.
 */
#define MAX_NUM_PLAYERS 2

/**
 * Enables a GUI that, while opem, allows plugging/unplugging controllers and changing the controller order.
 * Triggered by unplugging any active controller.
 */
#define ENABLE_STATUS_REPOLLING_GUI

/**
 * Allows the player to use the button combo defined in input.h to trigger status repolling at any time during gameplay.
 */
// #define ENABLE_STATUS_REPOLLING_COMBO_IN_GAMEPLAY

/**
 * Highlights the currently pressed buttons on controllers in the status repolling GUI.
 */
#define CONTROLLERS_INPUT_DISPLAY

/**
 * Informs supported emulators to default to GameCube controller inputs.
 */
// #define EMU_DEFAULT_TO_GCN

/**
 * RCVI hack. Increases performance on emulator, and does nothing on console.
 * Might break on some emulators. Use at your own risk, and don't use it unless you actually need the extra performance.
 */
// #define RCVI_HACK

/**
 * Screen Size Defines.
 */
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

/**
 * Height of the black borders at the top and bottom of the screen for NTSC Versions. You can set it to different values for console and emulator.
 * There is generally no reason to have a value other than 0 for emulator. As for console, it provides a (small) performance boost.
 */
#define BORDER_HEIGHT_CONSOLE  0
#define BORDER_HEIGHT_EMULATOR 0
