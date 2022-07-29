#define RELAYS_ENABLED_PIN PIND
#define RELAYS_ENABLED_DDR DDRD
#define RELAYS_ENABLED_BIT PD6
#define RELAYS_ENABLED_PINNUM _BV(6)
#define relays_enabled() !(RELAYS_ENABLED_PIN & RELAYS_ENABLED_PINNUM)

#define RELAYS_FORCED_ON_PIN PINE
#define RELAYS_FORCED_ON_DDR DDRE
#define RELAYS_FORCED_ON_BIT PE6
#define RELAYS_FORCED_ON_PINNUM _BV(6)
#define relays_forced_on() !(RELAYS_FORCED_ON_PIN & RELAYS_FORCED_ON_PINNUM)

#define AC_RELAY_PORT PORTB
#define AC_RELAY_DDR DDRB
#define AC_RELAY_BIT PB4
#define AC_RELAY_PINNUM _BV(4)
#define ac_off() AC_RELAY_PORT &= ~AC_RELAY_PINNUM
#define ac_on() AC_RELAY_PORT |= AC_RELAY_PINNUM

#define CURRENT_LOOP_RELAY_PORT PORTD
#define CURRENT_LOOP_RELAY_DDR DDRD
#define CURRENT_LOOP_RELAY_BIT PD1
#define CURRENT_LOOP_RELAY_PINNUM _BV(1)
#define current_loop_off() CURRENT_LOOP_RELAY_PORT &= ~CURRENT_LOOP_RELAY_PINNUM
#define current_loop_on() CURRENT_LOOP_RELAY_PORT |= CURRENT_LOOP_RELAY_PINNUM

#define SOFTUART_RXPIN PINB
#define SOFTUART_RXDDR DDRB
#define SOFTUART_RXBIT PB6
#define SOFTUART_RXPINNUM _BV(6)

#define SOFTUART_TXPORT PORTD
#define SOFTUART_TXDDR DDRD
#define SOFTUART_TXBIT PD7
#define SOFTUART_TXPINNUM _BV(7)

#define TX_LED_PORT PORTD
#define RX_LED_PORT PORTD
#define TX_LED_DDR DDRD
#define RX_LED_DDR DDRD
#define TX_LED 0
#define RX_LED 4
#define TX_LEDPIN _BV(TX_LED)
#define RX_LEDPIN _BV(RX_LED)

#define tx_led_on() TX_LED_PORT |= TX_LEDPIN
#define tx_led_off() TX_LED_PORT &= ~TX_LEDPIN
#define rx_led_on() RX_LED_PORT |= RX_LEDPIN
#define rx_led_off() RX_LED_PORT &= ~RX_LEDPIN