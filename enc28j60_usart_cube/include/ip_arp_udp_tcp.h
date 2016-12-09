/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 * Author: Guido Socher 
 * Copyright: GPL V2
 *
 * IP/ARP/UDP/TCP functions
 *
 * Chip type           : ATMEGA88 with ENC28J60
 *********************************************/


/*********************************************
 * modified: 2007-08-08
 * Author  : awake
 * Copyright: GPL V2
 * http://www.icdev.com.cn/?2213/
 * Host chip: ADUC7026
**********************************************/



//@{
#ifndef IP_ARP_UDP_TCP_H
#define IP_ARP_UDP_TCP_H

// you must call this function once before you use any of the other functions:
extern void init_ip_arp_udp_tcp(uint8_t* mymac, uint8_t* myip,
   uint8_t wwwp);
//
extern uint8_t eth_type_is_arp_and_my_ip(uint8_t* buf,
   unsigned int len);
extern uint8_t eth_type_is_ip_and_my_ip(uint8_t* buf,
   unsigned int len);
extern void make_arp_answer_from_request(uint8_t* buf);
extern void make_echo_reply_from_request(uint8_t* buf, unsigned int len);
extern void make_udp_reply_from_request(uint8_t* buf, char* data,
   uint8_t datalen, unsigned int port);


extern void make_tcp_synack_from_syn(uint8_t* buf);
extern void init_len_info(uint8_t* buf);
extern unsigned int get_tcp_data_pointer(void);
extern unsigned int fill_tcp_data_p(uint8_t* buf, unsigned int pos,
   const uint8_t* progmem_s);
extern unsigned int fill_tcp_data(uint8_t* buf, unsigned int pos,
   const char* s);
extern void make_tcp_ack_from_any(uint8_t* buf);
extern void make_tcp_ack_with_data(uint8_t* buf, unsigned int dlen);




#endif /* IP_ARP_UDP_TCP_H */
//@}
