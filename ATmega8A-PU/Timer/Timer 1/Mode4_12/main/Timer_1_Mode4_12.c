#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL

uint8_t counter = 0;
const uint8_t segmentPatterns[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90 };
static uint8_t led_counter = 0;
 /* Sử dụng biến static để lưu trữ lần đếm nháy của led, (Led on -> off lần 1, led_counter+=2 , Led on -> off lần 2, led_counter+=2 , Led on -> off lần 3, led_counter+=2 )
 Nếu không có biến static (Led on -> off lần 1, led_counter = 0, Led on -> off lần 2, led_counter = 0, Led on -> off lần 3, led_counter = 0)
 Như vậy led_counter không đếm lên => không đủ điều kiện if Line 33	*/
void KhaiBao() {
	DDRC |= (1 << 5); //Set Output PB0 cho LED
	DDRD |= 0x7F; //Set Output từ PD0->PD6 cho Led 7 đoạn
	PORTC |= (1 << 5); //Bật Led
	TCCR1B |= (1 << WGM12) | (1 << CS12); //Set bit dùng Mode 4 (CTC) và Prescale 256
	/*TCNT1 = 0; (BOTTOM)
	BOTTOM không cần khai báo vì nó luôn = 0
	Nếu BOTTOM = N thì phải khai báo*/
	OCR1A = 31250; //TOP, giá trị so sánh với BOTTOM ++
	TIMSK |= (1 << OCIE1A); //Cho phép ngắt khi BOTTOM++ = TOP
	sei();
}
int main(void) {
	KhaiBao();
	while (1) 
	{
	}
}
ISR(TIMER1_COMPA_vect) {
	PORTC ^= (1 << 5); //Đổi trạng thái Led (Tắt)
	led_counter++; // Mỗi lần LED Bật (Line 11) và Tắt (Line 28) thì biến này sẽ +2 (bật +1) (tắt +1)
	if (led_counter >= 6) 
	{
		counter++; //Mỗi khi biến led trên (led counter) bật tắt đủ 3 lần (tổng cộng 6 nhịp) thì led 7 đoạn sẽ nâng lên 1 đơn vị
		if (counter > 9) { // Nếu Led đã đếm đến số 9 thì quay lại số 0
			counter = 0;
		}
		PORTD = segmentPatterns[counter]; //Bật led 7 đoạn chạy theo mã hex Line 6
		led_counter = 0; //Mỗi khi biến led trên (led counter) bật tắt đủ 3 lần (tổng cộng 6 nhịp) thì quay lại nhịp đầu tiên
	}
}