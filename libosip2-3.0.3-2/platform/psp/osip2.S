	.set noreorder

#include "pspimport.s"

// Build files
// osip2_0000.o osip2_0001.o osip2_0002.o osip2_0003.o osip2_0004.o osip2_0005.o osip2_0006.o osip2_0007.o osip2_0008.o osip2_0009.o osip2_0010.o osip2_0011.o osip2_0012.o osip2_0013.o osip2_0014.o osip2_0015.o osip2_0016.o osip2_0017.o osip2_0018.o osip2_0019.o osip2_0020.o osip2_0021.o osip2_0022.o osip2_0023.o osip2_0024.o osip2_0025.o osip2_0026.o osip2_0027.o osip2_0028.o osip2_0029.o osip2_0030.o osip2_0031.o osip2_0032.o osip2_0033.o osip2_0034.o osip2_0035.o osip2_0036.o osip2_0037.o osip2_0038.o osip2_0039.o osip2_0040.o osip2_0041.o osip2_0042.o osip2_0043.o osip2_0044.o osip2_0045.o osip2_0046.o osip2_0047.o osip2_0048.o osip2_0049.o osip2_0050.o osip2_0051.o osip2_0052.o osip2_0053.o osip2_0054.o osip2_0055.o osip2_0056.o osip2_0057.o osip2_0058.o osip2_0059.o osip2_0060.o osip2_0061.o osip2_0062.o osip2_0063.o osip2_0064.o osip2_0065.o osip2_0066.o osip2_0067.o osip2_0068.o osip2_0069.o osip2_0070.o 

#ifdef F_osip2_0000
	IMPORT_START "osip2",0x00080000
#endif
#ifdef F_osip2_0001
	IMPORT_FUNC  "osip2",0x76B254FE,evt_set_type_incoming_sipmessage
#endif
#ifdef F_osip2_0002
	IMPORT_FUNC  "osip2",0x7658D9FF,evt_set_type_outgoing_sipmessage
#endif
#ifdef F_osip2_0003
	IMPORT_FUNC  "osip2",0x919A81F6,osip_create_transaction
#endif
#ifdef F_osip2_0004
	IMPORT_FUNC  "osip2",0x1690E94A,osip_dialog_free
#endif
#ifdef F_osip2_0005
	IMPORT_FUNC  "osip2",0x0F15847A,osip_dialog_init_as_uac
#endif
#ifdef F_osip2_0006
	IMPORT_FUNC  "osip2",0x02B26DD8,osip_dialog_init_as_uas
#endif
#ifdef F_osip2_0007
	IMPORT_FUNC  "osip2",0xAF56DA87,osip_dialog_match_as_uac
#endif
#ifdef F_osip2_0008
	IMPORT_FUNC  "osip2",0x53547D65,osip_dialog_match_as_uas
#endif
#ifdef F_osip2_0009
	IMPORT_FUNC  "osip2",0x12B5FB16,osip_dialog_set_state
#endif
#ifdef F_osip2_0010
	IMPORT_FUNC  "osip2",0x5C012063,osip_dialog_update_osip_cseq_as_uas
#endif
#ifdef F_osip2_0011
	IMPORT_FUNC  "osip2",0xA5F9B862,osip_dialog_update_route_set_as_uac
#endif
#ifdef F_osip2_0012
	IMPORT_FUNC  "osip2",0x209E8F4C,osip_dialog_update_route_set_as_uas
#endif
#ifdef F_osip2_0013
	IMPORT_FUNC  "osip2",0xBB134950,osip_dialog_update_tag_as_uac
#endif
#ifdef F_osip2_0014
	IMPORT_FUNC  "osip2",0x62C1259E,osip_event_free
#endif
#ifdef F_osip2_0015
	IMPORT_FUNC  "osip2",0xDCAD841E,osip_fifo_add
#endif
#ifdef F_osip2_0016
	IMPORT_FUNC  "osip2",0x982E37F8,osip_fifo_free
#endif
#ifdef F_osip2_0017
	IMPORT_FUNC  "osip2",0x24AD7191,osip_fifo_get
#endif
#ifdef F_osip2_0018
	IMPORT_FUNC  "osip2",0x9F5E99D0,osip_fifo_init
#endif
#ifdef F_osip2_0019
	IMPORT_FUNC  "osip2",0x16959EF9,osip_fifo_insert
#endif
#ifdef F_osip2_0020
	IMPORT_FUNC  "osip2",0x24135E8C,osip_fifo_size
#endif
#ifdef F_osip2_0021
	IMPORT_FUNC  "osip2",0x83E5B634,osip_fifo_tryget
#endif
#ifdef F_osip2_0022
	IMPORT_FUNC  "osip2",0xF28D0A43,osip_find_transaction_and_add_event
#endif
#ifdef F_osip2_0023
	IMPORT_FUNC  "osip2",0xAB0DFD9F,osip_get_application_context
#endif
#ifdef F_osip2_0024
	IMPORT_FUNC  "osip2",0xA8553A49,osip_ict_execute
#endif
#ifdef F_osip2_0025
	IMPORT_FUNC  "osip2",0x131EEF98,osip_ict_lock
#endif
#ifdef F_osip2_0026
	IMPORT_FUNC  "osip2",0x5FBADC36,osip_ict_set_destination
#endif
#ifdef F_osip2_0027
	IMPORT_FUNC  "osip2",0x7F48DA6E,osip_ict_unlock
#endif
#ifdef F_osip2_0028
	IMPORT_FUNC  "osip2",0x6AC2CAC0,osip_init
#endif
#ifdef F_osip2_0029
	IMPORT_FUNC  "osip2",0xF5C37136,osip_ist_execute
#endif
#ifdef F_osip2_0030
	IMPORT_FUNC  "osip2",0x8B5A80B4,osip_ist_lock
#endif
#ifdef F_osip2_0031
	IMPORT_FUNC  "osip2",0x345C2B7F,osip_ist_unlock
#endif
#ifdef F_osip2_0032
	IMPORT_FUNC  "osip2",0xA90B96C3,osip_new_outgoing_sipmessage
#endif
#ifdef F_osip2_0033
	IMPORT_FUNC  "osip2",0x8890CAD3,osip_nict_execute
#endif
#ifdef F_osip2_0034
	IMPORT_FUNC  "osip2",0x61F13599,osip_nict_lock
#endif
#ifdef F_osip2_0035
	IMPORT_FUNC  "osip2",0x006FF501,osip_nict_set_destination
#endif
#ifdef F_osip2_0036
	IMPORT_FUNC  "osip2",0xE038455D,osip_nict_unlock
#endif
#ifdef F_osip2_0037
	IMPORT_FUNC  "osip2",0x76F3D68D,osip_nist_execute
#endif
#ifdef F_osip2_0038
	IMPORT_FUNC  "osip2",0x14E1B7C0,osip_nist_lock
#endif
#ifdef F_osip2_0039
	IMPORT_FUNC  "osip2",0x294D547C,osip_nist_unlock
#endif
#ifdef F_osip2_0040
	IMPORT_FUNC  "osip2",0xFFA2D03D,osip_parse
#endif
#ifdef F_osip2_0041
	IMPORT_FUNC  "osip2",0xCCC17629,osip_release
#endif
#ifdef F_osip2_0042
	IMPORT_FUNC  "osip2",0xE3CFC27A,osip_remove_transaction
#endif
#ifdef F_osip2_0043
	IMPORT_FUNC  "osip2",0x24B59020,osip_set_application_context
#endif
#ifdef F_osip2_0044
	IMPORT_FUNC  "osip2",0xCE140274,osip_set_cb_send_message
#endif
#ifdef F_osip2_0045
	IMPORT_FUNC  "osip2",0x6AA565AC,osip_set_kill_transaction_callback
#endif
#ifdef F_osip2_0046
	IMPORT_FUNC  "osip2",0x1E104CC6,osip_set_message_callback
#endif
#ifdef F_osip2_0047
	IMPORT_FUNC  "osip2",0x2BDD44C4,osip_set_transport_error_callback
#endif
#ifdef F_osip2_0048
	IMPORT_FUNC  "osip2",0xA2156E82,osip_timers_ict_execute
#endif
#ifdef F_osip2_0049
	IMPORT_FUNC  "osip2",0x0FF2BEF4,osip_timers_ist_execute
#endif
#ifdef F_osip2_0050
	IMPORT_FUNC  "osip2",0xC1B5FAB3,osip_timers_nict_execute
#endif
#ifdef F_osip2_0051
	IMPORT_FUNC  "osip2",0xCDAEE78E,osip_timers_nist_execute
#endif
#ifdef F_osip2_0052
	IMPORT_FUNC  "osip2",0xABC593EE,osip_transaction_add_event
#endif
#ifdef F_osip2_0053
	IMPORT_FUNC  "osip2",0x8196FE37,osip_transaction_execute
#endif
#ifdef F_osip2_0054
	IMPORT_FUNC  "osip2",0x0D32C2B5,osip_transaction_find
#endif
#ifdef F_osip2_0055
	IMPORT_FUNC  "osip2",0x3A4B3DE6,osip_transaction_free
#endif
#ifdef F_osip2_0056
	IMPORT_FUNC  "osip2",0xE73B659B,osip_transaction_free2
#endif
#ifdef F_osip2_0057
	IMPORT_FUNC  "osip2",0xD374A626,osip_transaction_get_destination
#endif
#ifdef F_osip2_0058
	IMPORT_FUNC  "osip2",0x714F45AB,osip_transaction_get_your_instance
#endif
#ifdef F_osip2_0059
	IMPORT_FUNC  "osip2",0x3C4CA6D7,osip_transaction_init
#endif
#ifdef F_osip2_0060
	IMPORT_FUNC  "osip2",0x873235F5,osip_transaction_set_in_socket
#endif
#ifdef F_osip2_0061
	IMPORT_FUNC  "osip2",0x78FD2EA6,osip_transaction_set_out_socket
#endif
#ifdef F_osip2_0062
	IMPORT_FUNC  "osip2",0x9339A42B,osip_transaction_set_your_instance
#endif
#ifdef F_osip2_0063
	IMPORT_FUNC  "osip2",0x3EF4A450,osip_dialog_init_as_uac_with_remote_request
#endif
#ifdef F_osip2_0064
	IMPORT_FUNC  "osip2",0x08218388,osip_timers_gettimeout
#endif
#ifdef F_osip2_0065
	IMPORT_FUNC  "osip2",0x00DBF1CF,osip_retransmissions_execute
#endif
#ifdef F_osip2_0066
	IMPORT_FUNC  "osip2",0x89F7E744,osip_start_200ok_retransmissions
#endif
#ifdef F_osip2_0067
	IMPORT_FUNC  "osip2",0x7347856A,osip_start_ack_retransmissions
#endif
#ifdef F_osip2_0068
	IMPORT_FUNC  "osip2",0x9D8DE989,osip_stop_200ok_retransmissions
#endif
#ifdef F_osip2_0069
	IMPORT_FUNC  "osip2",0x91349028,osip_stop_retransmissions_from_dialog
#endif
#ifdef F_osip2_0070
	IMPORT_FUNC  "osip2",0x8B16026C,add_gettimeofday
#endif
