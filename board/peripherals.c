/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v7.0
processor: MKE02Z16xxx4
package_id: MKE02Z16VFM4
mcu_data: ksdk2_0
processor_version: 7.0.1
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 984879db-47a0-44e6-82ac-cf44e45456aa
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'msg'
- type_id: 'msg_6e2baaf3b97dbeef01c0043275f9a0e7'
- global_messages: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * UART1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'UART1'
- type: 'uart'
- mode: 'polling'
- custom_name_enabled: 'false'
- type_id: 'uart_88ab1eca0cddb7ee407685775de016d5'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'UART1'
- config_sets:
  - uartConfig_t:
    - uartConfig:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'BOARD_BootClockRUN'
      - baudRate_Bps: '9600'
      - parityMode: 'kUART_ParityDisabled'
      - stopBitCount: 'kUART_OneStopBit'
      - idleType: 'kUART_IdleTypeStartBit'
      - enableTx: 'true'
      - enableRx: 'true'
    - quick_selection: 'QuickSelection5'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const uart_config_t UART1_config = {
  .baudRate_Bps = 9600,
  .parityMode = kUART_ParityDisabled,
  .stopBitCount = kUART_OneStopBit,
  .idleType = kUART_IdleTypeStartBit,
  .enableTx = true,
  .enableRx = true
};

void UART1_init(void) {
  UART_Init(UART1_PERIPHERAL, &UART1_config, UART1_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  UART1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}