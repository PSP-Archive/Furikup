	.set noreorder

#include "pspimport.s"

// Build files
// osipparser2_0000.o osipparser2_0001.o osipparser2_0002.o osipparser2_0003.o osipparser2_0004.o osipparser2_0005.o osipparser2_0006.o osipparser2_0007.o osipparser2_0008.o osipparser2_0009.o osipparser2_0010.o osipparser2_0011.o osipparser2_0012.o osipparser2_0013.o osipparser2_0014.o osipparser2_0015.o osipparser2_0016.o osipparser2_0017.o osipparser2_0018.o osipparser2_0019.o osipparser2_0020.o osipparser2_0021.o osipparser2_0022.o osipparser2_0023.o osipparser2_0024.o osipparser2_0025.o osipparser2_0026.o osipparser2_0027.o osipparser2_0028.o osipparser2_0029.o osipparser2_0030.o osipparser2_0031.o osipparser2_0032.o osipparser2_0033.o osipparser2_0034.o osipparser2_0035.o osipparser2_0036.o osipparser2_0037.o osipparser2_0038.o osipparser2_0039.o osipparser2_0040.o osipparser2_0041.o osipparser2_0042.o osipparser2_0043.o osipparser2_0044.o osipparser2_0045.o osipparser2_0046.o osipparser2_0047.o osipparser2_0048.o osipparser2_0049.o osipparser2_0050.o osipparser2_0051.o osipparser2_0052.o osipparser2_0053.o osipparser2_0054.o osipparser2_0055.o osipparser2_0056.o osipparser2_0057.o osipparser2_0058.o osipparser2_0059.o osipparser2_0060.o osipparser2_0061.o osipparser2_0062.o osipparser2_0063.o osipparser2_0064.o osipparser2_0065.o osipparser2_0066.o osipparser2_0067.o osipparser2_0068.o osipparser2_0069.o osipparser2_0070.o osipparser2_0071.o osipparser2_0072.o osipparser2_0073.o osipparser2_0074.o osipparser2_0075.o osipparser2_0076.o osipparser2_0077.o osipparser2_0078.o osipparser2_0079.o osipparser2_0080.o osipparser2_0081.o osipparser2_0082.o osipparser2_0083.o osipparser2_0084.o osipparser2_0085.o osipparser2_0086.o osipparser2_0087.o osipparser2_0088.o osipparser2_0089.o osipparser2_0090.o osipparser2_0091.o osipparser2_0092.o osipparser2_0093.o osipparser2_0094.o osipparser2_0095.o osipparser2_0096.o osipparser2_0097.o osipparser2_0098.o osipparser2_0099.o osipparser2_0100.o osipparser2_0101.o osipparser2_0102.o osipparser2_0103.o osipparser2_0104.o osipparser2_0105.o osipparser2_0106.o osipparser2_0107.o osipparser2_0108.o osipparser2_0109.o osipparser2_0110.o osipparser2_0111.o osipparser2_0112.o osipparser2_0113.o osipparser2_0114.o osipparser2_0115.o osipparser2_0116.o osipparser2_0117.o osipparser2_0118.o osipparser2_0119.o osipparser2_0120.o osipparser2_0121.o osipparser2_0122.o osipparser2_0123.o osipparser2_0124.o osipparser2_0125.o osipparser2_0126.o osipparser2_0127.o osipparser2_0128.o osipparser2_0129.o osipparser2_0130.o osipparser2_0131.o osipparser2_0132.o osipparser2_0133.o osipparser2_0134.o osipparser2_0135.o osipparser2_0136.o osipparser2_0137.o osipparser2_0138.o osipparser2_0139.o osipparser2_0140.o osipparser2_0141.o osipparser2_0142.o osipparser2_0143.o osipparser2_0144.o osipparser2_0145.o osipparser2_0146.o osipparser2_0147.o osipparser2_0148.o osipparser2_0149.o osipparser2_0150.o osipparser2_0151.o osipparser2_0152.o osipparser2_0153.o osipparser2_0154.o osipparser2_0155.o osipparser2_0156.o osipparser2_0157.o osipparser2_0158.o osipparser2_0159.o osipparser2_0160.o osipparser2_0161.o osipparser2_0162.o osipparser2_0163.o osipparser2_0164.o osipparser2_0165.o osipparser2_0166.o osipparser2_0167.o osipparser2_0168.o osipparser2_0169.o osipparser2_0170.o osipparser2_0171.o osipparser2_0172.o osipparser2_0173.o osipparser2_0174.o osipparser2_0175.o osipparser2_0176.o osipparser2_0177.o osipparser2_0178.o osipparser2_0179.o osipparser2_0180.o osipparser2_0181.o osipparser2_0182.o osipparser2_0183.o osipparser2_0184.o osipparser2_0185.o osipparser2_0186.o osipparser2_0187.o osipparser2_0188.o osipparser2_0189.o osipparser2_0190.o osipparser2_0191.o osipparser2_0192.o osipparser2_0193.o osipparser2_0194.o osipparser2_0195.o osipparser2_0196.o osipparser2_0197.o osipparser2_0198.o osipparser2_0199.o osipparser2_0200.o osipparser2_0201.o osipparser2_0202.o osipparser2_0203.o osipparser2_0204.o osipparser2_0205.o osipparser2_0206.o osipparser2_0207.o osipparser2_0208.o osipparser2_0209.o osipparser2_0210.o osipparser2_0211.o osipparser2_0212.o osipparser2_0213.o osipparser2_0214.o osipparser2_0215.o osipparser2_0216.o osipparser2_0217.o osipparser2_0218.o osipparser2_0219.o osipparser2_0220.o osipparser2_0221.o osipparser2_0222.o osipparser2_0223.o osipparser2_0224.o osipparser2_0225.o osipparser2_0226.o osipparser2_0227.o osipparser2_0228.o osipparser2_0229.o osipparser2_0230.o osipparser2_0231.o osipparser2_0232.o osipparser2_0233.o osipparser2_0234.o osipparser2_0235.o osipparser2_0236.o osipparser2_0237.o osipparser2_0238.o osipparser2_0239.o osipparser2_0240.o osipparser2_0241.o osipparser2_0242.o osipparser2_0243.o osipparser2_0244.o osipparser2_0245.o osipparser2_0246.o osipparser2_0247.o osipparser2_0248.o osipparser2_0249.o osipparser2_0250.o osipparser2_0251.o osipparser2_0252.o osipparser2_0253.o osipparser2_0254.o osipparser2_0255.o osipparser2_0256.o osipparser2_0257.o osipparser2_0258.o osipparser2_0259.o osipparser2_0260.o osipparser2_0261.o osipparser2_0262.o osipparser2_0263.o osipparser2_0264.o osipparser2_0265.o osipparser2_0266.o osipparser2_0267.o osipparser2_0268.o osipparser2_0269.o osipparser2_0270.o osipparser2_0271.o osipparser2_0272.o osipparser2_0273.o osipparser2_0274.o osipparser2_0275.o osipparser2_0276.o osipparser2_0277.o osipparser2_0278.o osipparser2_0279.o osipparser2_0280.o osipparser2_0281.o osipparser2_0282.o osipparser2_0283.o osipparser2_0284.o osipparser2_0285.o osipparser2_0286.o osipparser2_0287.o osipparser2_0288.o osipparser2_0289.o osipparser2_0290.o osipparser2_0291.o osipparser2_0292.o osipparser2_0293.o osipparser2_0294.o osipparser2_0295.o osipparser2_0296.o osipparser2_0297.o osipparser2_0298.o osipparser2_0299.o osipparser2_0300.o osipparser2_0301.o osipparser2_0302.o osipparser2_0303.o osipparser2_0304.o osipparser2_0305.o osipparser2_0306.o osipparser2_0307.o osipparser2_0308.o osipparser2_0309.o osipparser2_0310.o osipparser2_0311.o osipparser2_0312.o osipparser2_0313.o osipparser2_0314.o osipparser2_0315.o osipparser2_0316.o osipparser2_0317.o osipparser2_0318.o osipparser2_0319.o osipparser2_0320.o osipparser2_0321.o osipparser2_0322.o osipparser2_0323.o osipparser2_0324.o osipparser2_0325.o osipparser2_0326.o osipparser2_0327.o osipparser2_0328.o osipparser2_0329.o osipparser2_0330.o osipparser2_0331.o osipparser2_0332.o osipparser2_0333.o osipparser2_0334.o osipparser2_0335.o osipparser2_0336.o osipparser2_0337.o osipparser2_0338.o osipparser2_0339.o osipparser2_0340.o osipparser2_0341.o osipparser2_0342.o osipparser2_0343.o osipparser2_0344.o osipparser2_0345.o osipparser2_0346.o osipparser2_0347.o osipparser2_0348.o osipparser2_0349.o osipparser2_0350.o osipparser2_0351.o osipparser2_0352.o osipparser2_0353.o osipparser2_0354.o osipparser2_0355.o osipparser2_0356.o osipparser2_0357.o osipparser2_0358.o osipparser2_0359.o osipparser2_0360.o osipparser2_0361.o osipparser2_0362.o osipparser2_0363.o osipparser2_0364.o osipparser2_0365.o osipparser2_0366.o osipparser2_0367.o osipparser2_0368.o osipparser2_0369.o osipparser2_0370.o osipparser2_0371.o osipparser2_0372.o osipparser2_0373.o osipparser2_0374.o osipparser2_0375.o osipparser2_0376.o osipparser2_0377.o osipparser2_0378.o osipparser2_0379.o osipparser2_0380.o osipparser2_0381.o osipparser2_0382.o osipparser2_0383.o 

#ifdef F_osipparser2_0000
	IMPORT_START "osipparser2",0x00080000
#endif
#ifdef F_osipparser2_0001
	IMPORT_FUNC  "osipparser2",0xC4DA3525,parser_init
#endif
#ifdef F_osipparser2_0002
	IMPORT_FUNC  "osipparser2",0x5FA9EA51,osip_accept_encoding_clone
#endif
#ifdef F_osipparser2_0003
	IMPORT_FUNC  "osipparser2",0x4EF148DF,osip_accept_encoding_free
#endif
#ifdef F_osipparser2_0004
	IMPORT_FUNC  "osipparser2",0xA5F8A7DB,osip_accept_encoding_get_element
#endif
#ifdef F_osipparser2_0005
	IMPORT_FUNC  "osipparser2",0x7139B1BE,osip_accept_encoding_init
#endif
#ifdef F_osipparser2_0006
	IMPORT_FUNC  "osipparser2",0x4862EEC6,osip_accept_encoding_parse
#endif
#ifdef F_osipparser2_0007
	IMPORT_FUNC  "osipparser2",0xBFC2C5EA,osip_accept_encoding_set_element
#endif
#ifdef F_osipparser2_0008
	IMPORT_FUNC  "osipparser2",0xF36A58CB,osip_accept_encoding_to_str
#endif
#ifdef F_osipparser2_0009
	IMPORT_FUNC  "osipparser2",0x33290F93,osip_atoi
#endif
#ifdef F_osipparser2_0010
	IMPORT_FUNC  "osipparser2",0x9FEBF146,osip_authorization_clone
#endif
#ifdef F_osipparser2_0011
	IMPORT_FUNC  "osipparser2",0xCA0AFCE6,osip_authorization_free
#endif
#ifdef F_osipparser2_0012
	IMPORT_FUNC  "osipparser2",0xDBFD2573,osip_authorization_get_algorithm
#endif
#ifdef F_osipparser2_0013
	IMPORT_FUNC  "osipparser2",0x7CD23853,osip_authorization_get_auth_type
#endif
#ifdef F_osipparser2_0014
	IMPORT_FUNC  "osipparser2",0x44730BA6,osip_authorization_get_cnonce
#endif
#ifdef F_osipparser2_0015
	IMPORT_FUNC  "osipparser2",0x12C1F429,osip_authorization_get_digest
#endif
#ifdef F_osipparser2_0016
	IMPORT_FUNC  "osipparser2",0x4E2830A4,osip_authorization_get_message_qop
#endif
#ifdef F_osipparser2_0017
	IMPORT_FUNC  "osipparser2",0x8591968C,osip_authorization_get_nonce
#endif
#ifdef F_osipparser2_0018
	IMPORT_FUNC  "osipparser2",0x83958304,osip_authorization_get_nonce_count
#endif
#ifdef F_osipparser2_0019
	IMPORT_FUNC  "osipparser2",0xAD7CCAEE,osip_authorization_get_opaque
#endif
#ifdef F_osipparser2_0020
	IMPORT_FUNC  "osipparser2",0x0145E6B7,osip_authorization_get_realm
#endif
#ifdef F_osipparser2_0021
	IMPORT_FUNC  "osipparser2",0xC720196B,osip_authorization_get_response
#endif
#ifdef F_osipparser2_0022
	IMPORT_FUNC  "osipparser2",0xAC80B7C1,osip_authorization_get_uri
#endif
#ifdef F_osipparser2_0023
	IMPORT_FUNC  "osipparser2",0x0C26F93C,osip_authorization_get_username
#endif
#ifdef F_osipparser2_0024
	IMPORT_FUNC  "osipparser2",0x4505DB12,osip_authorization_init
#endif
#ifdef F_osipparser2_0025
	IMPORT_FUNC  "osipparser2",0x61976231,osip_authorization_parse
#endif
#ifdef F_osipparser2_0026
	IMPORT_FUNC  "osipparser2",0x8BE37124,osip_authorization_set_algorithm
#endif
#ifdef F_osipparser2_0027
	IMPORT_FUNC  "osipparser2",0x64D50839,osip_authorization_set_auth_type
#endif
#ifdef F_osipparser2_0028
	IMPORT_FUNC  "osipparser2",0x1FBAB7E3,osip_authorization_set_cnonce
#endif
#ifdef F_osipparser2_0029
	IMPORT_FUNC  "osipparser2",0x2EF16A17,osip_authorization_set_digest
#endif
#ifdef F_osipparser2_0030
	IMPORT_FUNC  "osipparser2",0xA232DD86,osip_authorization_set_message_qop
#endif
#ifdef F_osipparser2_0031
	IMPORT_FUNC  "osipparser2",0xC2CA723B,osip_authorization_set_nonce
#endif
#ifdef F_osipparser2_0032
	IMPORT_FUNC  "osipparser2",0x003CC1FC,osip_authorization_set_nonce_count
#endif
#ifdef F_osipparser2_0033
	IMPORT_FUNC  "osipparser2",0xF599FF33,osip_authorization_set_opaque
#endif
#ifdef F_osipparser2_0034
	IMPORT_FUNC  "osipparser2",0x84F47894,osip_authorization_set_realm
#endif
#ifdef F_osipparser2_0035
	IMPORT_FUNC  "osipparser2",0xACDBC394,osip_authorization_set_response
#endif
#ifdef F_osipparser2_0036
	IMPORT_FUNC  "osipparser2",0x5CC0BDB3,osip_authorization_set_uri
#endif
#ifdef F_osipparser2_0037
	IMPORT_FUNC  "osipparser2",0xC025BFFF,osip_authorization_set_username
#endif
#ifdef F_osipparser2_0038
	IMPORT_FUNC  "osipparser2",0xACF00049,osip_authorization_to_str
#endif
#ifdef F_osipparser2_0039
	IMPORT_FUNC  "osipparser2",0xC11051AD,osip_body_clone
#endif
#ifdef F_osipparser2_0040
	IMPORT_FUNC  "osipparser2",0x45A847BE,osip_body_free
#endif
#ifdef F_osipparser2_0041
	IMPORT_FUNC  "osipparser2",0x51C8AFA8,osip_body_init
#endif
#ifdef F_osipparser2_0042
	IMPORT_FUNC  "osipparser2",0x659543C7,osip_body_parse
#endif
#ifdef F_osipparser2_0043
	IMPORT_FUNC  "osipparser2",0xBBAFE356,osip_body_parse_mime
#endif
#ifdef F_osipparser2_0044
	IMPORT_FUNC  "osipparser2",0x668E160C,osip_body_set_contenttype
#endif
#ifdef F_osipparser2_0045
	IMPORT_FUNC  "osipparser2",0x8C8F1210,osip_body_set_header
#endif
#ifdef F_osipparser2_0046
	IMPORT_FUNC  "osipparser2",0xA0A36EF4,osip_body_to_str
#endif
#ifdef F_osipparser2_0047
	IMPORT_FUNC  "osipparser2",0x7A506C4C,osip_build_random_number
#endif
#ifdef F_osipparser2_0048
	IMPORT_FUNC  "osipparser2",0xABB1B453,osip_call_id_clone
#endif
#ifdef F_osipparser2_0049
	IMPORT_FUNC  "osipparser2",0x805CA572,osip_call_id_free
#endif
#ifdef F_osipparser2_0050
	IMPORT_FUNC  "osipparser2",0x86FB576B,osip_call_id_get_host
#endif
#ifdef F_osipparser2_0051
	IMPORT_FUNC  "osipparser2",0x5A11045B,osip_call_id_get_number
#endif
#ifdef F_osipparser2_0052
	IMPORT_FUNC  "osipparser2",0x375B4B53,osip_call_id_init
#endif
#ifdef F_osipparser2_0053
	IMPORT_FUNC  "osipparser2",0x7A4F7D40,osip_call_id_match
#endif
#ifdef F_osipparser2_0054
	IMPORT_FUNC  "osipparser2",0x3013541A,osip_call_id_parse
#endif
#ifdef F_osipparser2_0055
	IMPORT_FUNC  "osipparser2",0xB8270998,osip_call_id_set_host
#endif
#ifdef F_osipparser2_0056
	IMPORT_FUNC  "osipparser2",0xEA99B524,osip_call_id_set_number
#endif
#ifdef F_osipparser2_0057
	IMPORT_FUNC  "osipparser2",0x6E45F9A2,osip_call_id_to_str
#endif
#ifdef F_osipparser2_0058
	IMPORT_FUNC  "osipparser2",0x2EF63A47,osip_call_info_clone
#endif
#ifdef F_osipparser2_0059
	IMPORT_FUNC  "osipparser2",0xD192502F,osip_call_info_free
#endif
#ifdef F_osipparser2_0060
	IMPORT_FUNC  "osipparser2",0x2B650521,osip_call_info_get_uri
#endif
#ifdef F_osipparser2_0061
	IMPORT_FUNC  "osipparser2",0xBD78E7F9,osip_call_info_init
#endif
#ifdef F_osipparser2_0062
	IMPORT_FUNC  "osipparser2",0x1DD4C269,osip_call_info_parse
#endif
#ifdef F_osipparser2_0063
	IMPORT_FUNC  "osipparser2",0x5E997496,osip_call_info_set_uri
#endif
#ifdef F_osipparser2_0064
	IMPORT_FUNC  "osipparser2",0xFB350831,osip_call_info_to_str
#endif
#ifdef F_osipparser2_0065
	IMPORT_FUNC  "osipparser2",0x1C98587F,osip_clrspace
#endif
#ifdef F_osipparser2_0066
	IMPORT_FUNC  "osipparser2",0x4C5D99F9,osip_contact_clone
#endif
#ifdef F_osipparser2_0067
	IMPORT_FUNC  "osipparser2",0xFD0115E7,osip_contact_free
#endif
#ifdef F_osipparser2_0068
	IMPORT_FUNC  "osipparser2",0x573A0464,osip_contact_init
#endif
#ifdef F_osipparser2_0069
	IMPORT_FUNC  "osipparser2",0x8DD44B6A,osip_contact_parse
#endif
#ifdef F_osipparser2_0070
	IMPORT_FUNC  "osipparser2",0x96862FC6,osip_contact_to_str
#endif
#ifdef F_osipparser2_0071
	IMPORT_FUNC  "osipparser2",0x6C09B7C0,osip_content_disposition_parse
#endif
#ifdef F_osipparser2_0072
	IMPORT_FUNC  "osipparser2",0xEDBCBEA5,osip_content_length_clone
#endif
#ifdef F_osipparser2_0073
	IMPORT_FUNC  "osipparser2",0x92E3991C,osip_content_length_free
#endif
#ifdef F_osipparser2_0074
	IMPORT_FUNC  "osipparser2",0x960024E6,osip_content_length_init
#endif
#ifdef F_osipparser2_0075
	IMPORT_FUNC  "osipparser2",0xF2F20E6A,osip_content_length_parse
#endif
#ifdef F_osipparser2_0076
	IMPORT_FUNC  "osipparser2",0x9DF4FE1F,osip_content_length_to_str
#endif
#ifdef F_osipparser2_0077
	IMPORT_FUNC  "osipparser2",0x39946C30,osip_content_type_clone
#endif
#ifdef F_osipparser2_0078
	IMPORT_FUNC  "osipparser2",0x5C239443,osip_content_type_free
#endif
#ifdef F_osipparser2_0079
	IMPORT_FUNC  "osipparser2",0xA1BDAB68,osip_content_type_init
#endif
#ifdef F_osipparser2_0080
	IMPORT_FUNC  "osipparser2",0xB5E2B47E,osip_content_type_parse
#endif
#ifdef F_osipparser2_0081
	IMPORT_FUNC  "osipparser2",0x83ACEFF9,osip_content_type_to_str
#endif
#ifdef F_osipparser2_0082
	IMPORT_FUNC  "osipparser2",0x4C1DB43C,osip_cseq_clone
#endif
#ifdef F_osipparser2_0083
	IMPORT_FUNC  "osipparser2",0x0318D9C8,osip_cseq_free
#endif
#ifdef F_osipparser2_0084
	IMPORT_FUNC  "osipparser2",0xFFC83576,osip_cseq_get_method
#endif
#ifdef F_osipparser2_0085
	IMPORT_FUNC  "osipparser2",0x7EF7C814,osip_cseq_get_number
#endif
#ifdef F_osipparser2_0086
	IMPORT_FUNC  "osipparser2",0x865B812C,osip_cseq_init
#endif
#ifdef F_osipparser2_0087
	IMPORT_FUNC  "osipparser2",0x2B4CF2F3,osip_cseq_match
#endif
#ifdef F_osipparser2_0088
	IMPORT_FUNC  "osipparser2",0x7BA60A55,osip_cseq_parse
#endif
#ifdef F_osipparser2_0089
	IMPORT_FUNC  "osipparser2",0x59FB489B,osip_cseq_set_method
#endif
#ifdef F_osipparser2_0090
	IMPORT_FUNC  "osipparser2",0xCC795E8D,osip_cseq_set_number
#endif
#ifdef F_osipparser2_0091
	IMPORT_FUNC  "osipparser2",0xDEEA35CF,osip_cseq_to_str
#endif
#ifdef F_osipparser2_0092
	IMPORT_FUNC  "osipparser2",0xA509703C,osip_free
#endif
#ifdef F_osipparser2_0093
	IMPORT_FUNC  "osipparser2",0x831E8E41,osip_from_clone
#endif
#ifdef F_osipparser2_0094
	IMPORT_FUNC  "osipparser2",0xECBC0EF0,osip_from_compare
#endif
#ifdef F_osipparser2_0095
	IMPORT_FUNC  "osipparser2",0x4E1133A5,osip_from_free
#endif
#ifdef F_osipparser2_0096
	IMPORT_FUNC  "osipparser2",0x69C06367,osip_from_get_displayname
#endif
#ifdef F_osipparser2_0097
	IMPORT_FUNC  "osipparser2",0x430ECA6B,osip_from_get_url
#endif
#ifdef F_osipparser2_0098
	IMPORT_FUNC  "osipparser2",0x7EACB8F4,osip_from_init
#endif
#ifdef F_osipparser2_0099
	IMPORT_FUNC  "osipparser2",0xFFE5D410,osip_from_param_get
#endif
#ifdef F_osipparser2_0100
	IMPORT_FUNC  "osipparser2",0x5A5AECAF,osip_from_parse
#endif
#ifdef F_osipparser2_0101
	IMPORT_FUNC  "osipparser2",0x8E5EF996,osip_from_set_displayname
#endif
#ifdef F_osipparser2_0102
	IMPORT_FUNC  "osipparser2",0x27F04360,osip_from_set_url
#endif
#ifdef F_osipparser2_0103
	IMPORT_FUNC  "osipparser2",0xAEEF3602,osip_from_tag_match
#endif
#ifdef F_osipparser2_0104
	IMPORT_FUNC  "osipparser2",0xD4EDB415,osip_from_to_str
#endif
#ifdef F_osipparser2_0105
	IMPORT_FUNC  "osipparser2",0x79CFFA32,osip_generic_param_get_name
#endif
#ifdef F_osipparser2_0106
	IMPORT_FUNC  "osipparser2",0x1E8CB15F,osip_generic_param_get_value
#endif
#ifdef F_osipparser2_0107
	IMPORT_FUNC  "osipparser2",0x7153DFF1,osip_generic_param_set_name
#endif
#ifdef F_osipparser2_0108
	IMPORT_FUNC  "osipparser2",0x25F0B24F,osip_generic_param_set_value
#endif
#ifdef F_osipparser2_0109
	IMPORT_FUNC  "osipparser2",0xA6AB9C6E,osip_header_clone
#endif
#ifdef F_osipparser2_0110
	IMPORT_FUNC  "osipparser2",0xD3227B36,osip_header_free
#endif
#ifdef F_osipparser2_0111
	IMPORT_FUNC  "osipparser2",0x33199CBE,osip_header_get_name
#endif
#ifdef F_osipparser2_0112
	IMPORT_FUNC  "osipparser2",0x718150B4,osip_header_get_value
#endif
#ifdef F_osipparser2_0113
	IMPORT_FUNC  "osipparser2",0x03CA2A49,osip_header_init
#endif
#ifdef F_osipparser2_0114
	IMPORT_FUNC  "osipparser2",0x53810618,osip_header_set_name
#endif
#ifdef F_osipparser2_0115
	IMPORT_FUNC  "osipparser2",0xF6E56242,osip_header_set_value
#endif
#ifdef F_osipparser2_0116
	IMPORT_FUNC  "osipparser2",0x8E9D363A,osip_header_to_str
#endif
#ifdef F_osipparser2_0117
	IMPORT_FUNC  "osipparser2",0xA6734B99,osip_is_trace_level_activate
#endif
#ifdef F_osipparser2_0118
	IMPORT_FUNC  "osipparser2",0x14771933,osip_list_add
#endif
#ifdef F_osipparser2_0119
	IMPORT_FUNC  "osipparser2",0x3BC262C9,osip_list_eol
#endif
#ifdef F_osipparser2_0120
	IMPORT_FUNC  "osipparser2",0x32CCC5B1,osip_list_get
#endif
#ifdef F_osipparser2_0121
	IMPORT_FUNC  "osipparser2",0x2DA3563E,osip_list_init
#endif
#ifdef F_osipparser2_0122
	IMPORT_FUNC  "osipparser2",0xD7FF7B18,osip_list_ofchar_free
#endif
#ifdef F_osipparser2_0123
	IMPORT_FUNC  "osipparser2",0x035297A6,osip_list_remove
#endif
#ifdef F_osipparser2_0124
	IMPORT_FUNC  "osipparser2",0x47EE0A65,osip_list_size
#endif
#ifdef F_osipparser2_0125
	IMPORT_FUNC  "osipparser2",0xB93C4A6C,osip_list_special_free
#endif
#ifdef F_osipparser2_0126
	IMPORT_FUNC  "osipparser2",0xFC3BE6EF,osip_malloc
#endif
#ifdef F_osipparser2_0127
	IMPORT_FUNC  "osipparser2",0x96779C83,osip_message_clone
#endif
#ifdef F_osipparser2_0128
	IMPORT_FUNC  "osipparser2",0x767AF906,osip_message_fix_last_via_header
#endif
#ifdef F_osipparser2_0129
	IMPORT_FUNC  "osipparser2",0xFC0327D9,osip_message_force_update
#endif
#ifdef F_osipparser2_0130
	IMPORT_FUNC  "osipparser2",0xE5687F8E,osip_message_free
#endif
#ifdef F_osipparser2_0131
	IMPORT_FUNC  "osipparser2",0xAAC97F0F,osip_message_get__property
#endif
#ifdef F_osipparser2_0132
	IMPORT_FUNC  "osipparser2",0xD50745F1,osip_message_get_accept
#endif
#ifdef F_osipparser2_0133
	IMPORT_FUNC  "osipparser2",0xEB44CF14,osip_message_get_accept_encoding
#endif
#ifdef F_osipparser2_0134
	IMPORT_FUNC  "osipparser2",0xCE71E3DB,osip_message_get_accept_language
#endif
#ifdef F_osipparser2_0135
	IMPORT_FUNC  "osipparser2",0x2849B255,osip_message_get_alert_info
#endif
#ifdef F_osipparser2_0136
	IMPORT_FUNC  "osipparser2",0xBB42D8B7,osip_message_get_allow
#endif
#ifdef F_osipparser2_0137
	IMPORT_FUNC  "osipparser2",0x79BB96B0,osip_message_get_authorization
#endif
#ifdef F_osipparser2_0138
	IMPORT_FUNC  "osipparser2",0x5ABBB072,osip_message_get_body
#endif
#ifdef F_osipparser2_0139
	IMPORT_FUNC  "osipparser2",0x9CBCE821,osip_message_get_call_id
#endif
#ifdef F_osipparser2_0140
	IMPORT_FUNC  "osipparser2",0xB21F5F2F,osip_message_get_call_info
#endif
#ifdef F_osipparser2_0141
	IMPORT_FUNC  "osipparser2",0x50CB64A6,osip_message_get_contact
#endif
#ifdef F_osipparser2_0142
	IMPORT_FUNC  "osipparser2",0x40C82E1F,osip_message_get_content_encoding
#endif
#ifdef F_osipparser2_0143
	IMPORT_FUNC  "osipparser2",0x9C24E5BE,osip_message_get_content_length
#endif
#ifdef F_osipparser2_0144
	IMPORT_FUNC  "osipparser2",0x3DEC238C,osip_message_get_content_type
#endif
#ifdef F_osipparser2_0145
	IMPORT_FUNC  "osipparser2",0x327385B7,osip_message_get_cseq
#endif
#ifdef F_osipparser2_0146
	IMPORT_FUNC  "osipparser2",0xFE011285,osip_message_get_error_info
#endif
#ifdef F_osipparser2_0147
	IMPORT_FUNC  "osipparser2",0x25E32550,osip_message_get_from
#endif
#ifdef F_osipparser2_0148
	IMPORT_FUNC  "osipparser2",0xA7252338,osip_message_get_header
#endif
#ifdef F_osipparser2_0149
	IMPORT_FUNC  "osipparser2",0x11794BA0,osip_message_get_method
#endif
#ifdef F_osipparser2_0150
	IMPORT_FUNC  "osipparser2",0x61D07CB9,osip_message_get_mime_version
#endif
#ifdef F_osipparser2_0151
	IMPORT_FUNC  "osipparser2",0x16BD3A7E,osip_message_get_proxy_authenticate
#endif
#ifdef F_osipparser2_0152
	IMPORT_FUNC  "osipparser2",0x21B02404,osip_message_get_proxy_authorization
#endif
#ifdef F_osipparser2_0153
	IMPORT_FUNC  "osipparser2",0xE30E994C,osip_message_get_reason
#endif
#ifdef F_osipparser2_0154
	IMPORT_FUNC  "osipparser2",0xFE650C3A,osip_message_get_reason_phrase
#endif
#ifdef F_osipparser2_0155
	IMPORT_FUNC  "osipparser2",0xAC868CDE,osip_message_get_record_route
#endif
#ifdef F_osipparser2_0156
	IMPORT_FUNC  "osipparser2",0x9A2247CB,osip_message_get_route
#endif
#ifdef F_osipparser2_0157
	IMPORT_FUNC  "osipparser2",0x7BE73368,osip_message_get_status_code
#endif
#ifdef F_osipparser2_0158
	IMPORT_FUNC  "osipparser2",0xE37E4E64,osip_message_get_to
#endif
#ifdef F_osipparser2_0159
	IMPORT_FUNC  "osipparser2",0x0923031E,osip_message_get_uri
#endif
#ifdef F_osipparser2_0160
	IMPORT_FUNC  "osipparser2",0x4C39A309,osip_message_get_version
#endif
#ifdef F_osipparser2_0161
	IMPORT_FUNC  "osipparser2",0x59BED119,osip_message_get_via
#endif
#ifdef F_osipparser2_0162
	IMPORT_FUNC  "osipparser2",0x0BA9C67B,osip_message_get_www_authenticate
#endif
#ifdef F_osipparser2_0163
	IMPORT_FUNC  "osipparser2",0x2CC201F7,osip_message_header_get_byname
#endif
#ifdef F_osipparser2_0164
	IMPORT_FUNC  "osipparser2",0x511FAD26,osip_message_init
#endif
#ifdef F_osipparser2_0165
	IMPORT_FUNC  "osipparser2",0xC3BAB66D,osip_message_parse
#endif
#ifdef F_osipparser2_0166
	IMPORT_FUNC  "osipparser2",0x4E00FDC6,osip_message_set_accept
#endif
#ifdef F_osipparser2_0167
	IMPORT_FUNC  "osipparser2",0x0975425A,osip_message_set_accept_encoding
#endif
#ifdef F_osipparser2_0168
	IMPORT_FUNC  "osipparser2",0xFF6A7392,osip_message_set_accept_language
#endif
#ifdef F_osipparser2_0169
	IMPORT_FUNC  "osipparser2",0x4842F22D,osip_message_set_alert_info
#endif
#ifdef F_osipparser2_0170
	IMPORT_FUNC  "osipparser2",0xA45038C2,osip_message_set_allow
#endif
#ifdef F_osipparser2_0171
	IMPORT_FUNC  "osipparser2",0xD562C861,osip_message_set_authorization
#endif
#ifdef F_osipparser2_0172
	IMPORT_FUNC  "osipparser2",0x9BF4FB34,osip_message_set_body
#endif
#ifdef F_osipparser2_0173
	IMPORT_FUNC  "osipparser2",0x0A581096,osip_message_set_body_mime
#endif
#ifdef F_osipparser2_0174
	IMPORT_FUNC  "osipparser2",0x89F49D52,osip_message_set_call_id
#endif
#ifdef F_osipparser2_0175
	IMPORT_FUNC  "osipparser2",0x03124445,osip_message_set_call_info
#endif
#ifdef F_osipparser2_0176
	IMPORT_FUNC  "osipparser2",0x9FF9FED7,osip_message_set_contact
#endif
#ifdef F_osipparser2_0177
	IMPORT_FUNC  "osipparser2",0x88795A08,osip_message_set_content_encoding
#endif
#ifdef F_osipparser2_0178
	IMPORT_FUNC  "osipparser2",0xFE3EC189,osip_message_set_content_length
#endif
#ifdef F_osipparser2_0179
	IMPORT_FUNC  "osipparser2",0x1AC77694,osip_message_set_content_type
#endif
#ifdef F_osipparser2_0180
	IMPORT_FUNC  "osipparser2",0xA4958011,osip_message_set_cseq
#endif
#ifdef F_osipparser2_0181
	IMPORT_FUNC  "osipparser2",0x99764DA1,osip_message_set_error_info
#endif
#ifdef F_osipparser2_0182
	IMPORT_FUNC  "osipparser2",0xD96B6799,osip_message_set_from
#endif
#ifdef F_osipparser2_0183
	IMPORT_FUNC  "osipparser2",0x82551A3E,osip_message_set_header
#endif
#ifdef F_osipparser2_0184
	IMPORT_FUNC  "osipparser2",0x2AEE2945,osip_message_set_method
#endif
#ifdef F_osipparser2_0185
	IMPORT_FUNC  "osipparser2",0xBB8CBF49,osip_message_set_mime_version
#endif
#ifdef F_osipparser2_0186
	IMPORT_FUNC  "osipparser2",0x21324A95,osip_message_set_proxy_authenticate
#endif
#ifdef F_osipparser2_0187
	IMPORT_FUNC  "osipparser2",0xC945CB59,osip_message_set_proxy_authorization
#endif
#ifdef F_osipparser2_0188
	IMPORT_FUNC  "osipparser2",0xF69BC3C1,osip_message_set_reason_phrase
#endif
#ifdef F_osipparser2_0189
	IMPORT_FUNC  "osipparser2",0x0F67B0B7,osip_message_set_record_route
#endif
#ifdef F_osipparser2_0190
	IMPORT_FUNC  "osipparser2",0x0115464F,osip_message_set_route
#endif
#ifdef F_osipparser2_0191
	IMPORT_FUNC  "osipparser2",0x517B9136,osip_message_set_status_code
#endif
#ifdef F_osipparser2_0192
	IMPORT_FUNC  "osipparser2",0x2830875C,osip_message_set_to
#endif
#ifdef F_osipparser2_0193
	IMPORT_FUNC  "osipparser2",0x2A6F1F05,osip_message_set_topheader
#endif
#ifdef F_osipparser2_0194
	IMPORT_FUNC  "osipparser2",0x4965B208,osip_message_set_uri
#endif
#ifdef F_osipparser2_0195
	IMPORT_FUNC  "osipparser2",0xC6E9E57F,osip_message_set_version
#endif
#ifdef F_osipparser2_0196
	IMPORT_FUNC  "osipparser2",0x4F029454,osip_message_set_via
#endif
#ifdef F_osipparser2_0197
	IMPORT_FUNC  "osipparser2",0x45C0B8A4,osip_message_set_www_authenticate
#endif
#ifdef F_osipparser2_0198
	IMPORT_FUNC  "osipparser2",0xCB4E0B76,osip_message_to_str
#endif
#ifdef F_osipparser2_0199
	IMPORT_FUNC  "osipparser2",0x0314B0B8,osip_record_route_free
#endif
#ifdef F_osipparser2_0200
	IMPORT_FUNC  "osipparser2",0x81236E32,osip_record_route_init
#endif
#ifdef F_osipparser2_0201
	IMPORT_FUNC  "osipparser2",0xCEC00B9C,osip_record_route_parse
#endif
#ifdef F_osipparser2_0202
	IMPORT_FUNC  "osipparser2",0x78841B18,osip_record_route_to_str
#endif
#ifdef F_osipparser2_0203
	IMPORT_FUNC  "osipparser2",0x8B441859,osip_route_free
#endif
#ifdef F_osipparser2_0204
	IMPORT_FUNC  "osipparser2",0x83B729FF,osip_route_init
#endif
#ifdef F_osipparser2_0205
	IMPORT_FUNC  "osipparser2",0x7A96FD08,osip_route_parse
#endif
#ifdef F_osipparser2_0206
	IMPORT_FUNC  "osipparser2",0x1E9D8AAF,osip_route_to_str
#endif
#ifdef F_osipparser2_0207
	IMPORT_FUNC  "osipparser2",0xF00747CB,osip_strcasecmp
#endif
#ifdef F_osipparser2_0208
	IMPORT_FUNC  "osipparser2",0x10E7F4DA,osip_strdup
#endif
#ifdef F_osipparser2_0209
	IMPORT_FUNC  "osipparser2",0xBC30A31C,osip_strdup_without_quote
#endif
#ifdef F_osipparser2_0210
	IMPORT_FUNC  "osipparser2",0xB6781CB8,osip_strncasecmp
#endif
#ifdef F_osipparser2_0211
	IMPORT_FUNC  "osipparser2",0xFDA66E00,osip_strncpy
#endif
#ifdef F_osipparser2_0212
	IMPORT_FUNC  "osipparser2",0x1B81C315,osip_to_clone
#endif
#ifdef F_osipparser2_0213
	IMPORT_FUNC  "osipparser2",0xE1CE8C9E,osip_to_free
#endif
#ifdef F_osipparser2_0214
	IMPORT_FUNC  "osipparser2",0x4C56AB8F,osip_to_init
#endif
#ifdef F_osipparser2_0215
	IMPORT_FUNC  "osipparser2",0x7AB41A2F,osip_to_parse
#endif
#ifdef F_osipparser2_0216
	IMPORT_FUNC  "osipparser2",0xF430CFE2,osip_to_tag_match
#endif
#ifdef F_osipparser2_0217
	IMPORT_FUNC  "osipparser2",0x58D45BA0,osip_to_to_str
#endif
#ifdef F_osipparser2_0218
	IMPORT_FUNC  "osipparser2",0xD810642B,osip_tolower
#endif
#ifdef F_osipparser2_0219
	IMPORT_FUNC  "osipparser2",0xAF1E958A,osip_trace
#endif
#ifdef F_osipparser2_0220
	IMPORT_FUNC  "osipparser2",0x923011A0,osip_trace_disable_level
#endif
#ifdef F_osipparser2_0221
	IMPORT_FUNC  "osipparser2",0xD885DF84,osip_trace_enable_level
#endif
#ifdef F_osipparser2_0222
	IMPORT_FUNC  "osipparser2",0x3BC5C125,osip_trace_initialize
#endif
#ifdef F_osipparser2_0223
	IMPORT_FUNC  "osipparser2",0x1BC1E7ED,osip_trace_initialize_syslog
#endif
#ifdef F_osipparser2_0224
	IMPORT_FUNC  "osipparser2",0x233AD341,osip_uri_clone
#endif
#ifdef F_osipparser2_0225
	IMPORT_FUNC  "osipparser2",0x09238742,osip_uri_free
#endif
#ifdef F_osipparser2_0226
	IMPORT_FUNC  "osipparser2",0x602B70D1,osip_uri_get_host
#endif
#ifdef F_osipparser2_0227
	IMPORT_FUNC  "osipparser2",0x403E48E7,osip_uri_get_password
#endif
#ifdef F_osipparser2_0228
	IMPORT_FUNC  "osipparser2",0x754E4C51,osip_uri_get_port
#endif
#ifdef F_osipparser2_0229
	IMPORT_FUNC  "osipparser2",0x0F88071D,osip_uri_get_scheme
#endif
#ifdef F_osipparser2_0230
	IMPORT_FUNC  "osipparser2",0x56D35F69,osip_uri_get_username
#endif
#ifdef F_osipparser2_0231
	IMPORT_FUNC  "osipparser2",0x52D31234,osip_uri_init
#endif
#ifdef F_osipparser2_0232
	IMPORT_FUNC  "osipparser2",0x481E2512,osip_uri_param_add
#endif
#ifdef F_osipparser2_0233
	IMPORT_FUNC  "osipparser2",0xC9CDBB4F,osip_uri_param_clone
#endif
#ifdef F_osipparser2_0234
	IMPORT_FUNC  "osipparser2",0x00639AA6,osip_uri_param_free
#endif
#ifdef F_osipparser2_0235
	IMPORT_FUNC  "osipparser2",0xFCF7B60F,osip_uri_param_freelist
#endif
#ifdef F_osipparser2_0236
	IMPORT_FUNC  "osipparser2",0x1CCB55DA,osip_uri_param_get_byname
#endif
#ifdef F_osipparser2_0237
	IMPORT_FUNC  "osipparser2",0xDA83763D,osip_uri_param_init
#endif
#ifdef F_osipparser2_0238
	IMPORT_FUNC  "osipparser2",0x0C01E669,osip_uri_param_set
#endif
#ifdef F_osipparser2_0239
	IMPORT_FUNC  "osipparser2",0x10DF18C0,osip_uri_parse
#endif
#ifdef F_osipparser2_0240
	IMPORT_FUNC  "osipparser2",0xD70C9D3C,osip_uri_parse_headers
#endif
#ifdef F_osipparser2_0241
	IMPORT_FUNC  "osipparser2",0x5ACF3A1A,osip_uri_parse_params
#endif
#ifdef F_osipparser2_0242
	IMPORT_FUNC  "osipparser2",0x974F0165,osip_uri_set_host
#endif
#ifdef F_osipparser2_0243
	IMPORT_FUNC  "osipparser2",0xBD780D55,osip_uri_set_password
#endif
#ifdef F_osipparser2_0244
	IMPORT_FUNC  "osipparser2",0xBAA286CC,osip_uri_set_port
#endif
#ifdef F_osipparser2_0245
	IMPORT_FUNC  "osipparser2",0xADD9AA3A,osip_uri_set_scheme
#endif
#ifdef F_osipparser2_0246
	IMPORT_FUNC  "osipparser2",0xDC16F42E,osip_uri_set_username
#endif
#ifdef F_osipparser2_0247
	IMPORT_FUNC  "osipparser2",0x5F65FD0A,osip_uri_to_str
#endif
#ifdef F_osipparser2_0248
	IMPORT_FUNC  "osipparser2",0x83E49483,osip_uri_to_str_canonical
#endif
#ifdef F_osipparser2_0249
	IMPORT_FUNC  "osipparser2",0x28271621,osip_usleep
#endif
#ifdef F_osipparser2_0250
	IMPORT_FUNC  "osipparser2",0xCBC0CFDD,osip_via_clone
#endif
#ifdef F_osipparser2_0251
	IMPORT_FUNC  "osipparser2",0x51FDD7E3,osip_via_free
#endif
#ifdef F_osipparser2_0252
	IMPORT_FUNC  "osipparser2",0xE89CC3E1,osip_via_init
#endif
#ifdef F_osipparser2_0253
	IMPORT_FUNC  "osipparser2",0xCCEA04A1,osip_via_match
#endif
#ifdef F_osipparser2_0254
	IMPORT_FUNC  "osipparser2",0xF17AC1F2,osip_via_parse
#endif
#ifdef F_osipparser2_0255
	IMPORT_FUNC  "osipparser2",0x760C0110,osip_via_to_str
#endif
#ifdef F_osipparser2_0256
	IMPORT_FUNC  "osipparser2",0x11BC42AC,osip_www_authenticate_clone
#endif
#ifdef F_osipparser2_0257
	IMPORT_FUNC  "osipparser2",0xCD2E0E6F,osip_www_authenticate_free
#endif
#ifdef F_osipparser2_0258
	IMPORT_FUNC  "osipparser2",0xF81CC3D2,osip_www_authenticate_get_algorithm
#endif
#ifdef F_osipparser2_0259
	IMPORT_FUNC  "osipparser2",0x2D3397A9,osip_www_authenticate_get_auth_type
#endif
#ifdef F_osipparser2_0260
	IMPORT_FUNC  "osipparser2",0xE00B2C4E,osip_www_authenticate_get_domain
#endif
#ifdef F_osipparser2_0261
	IMPORT_FUNC  "osipparser2",0xB57DC8B1,osip_www_authenticate_get_nonce
#endif
#ifdef F_osipparser2_0262
	IMPORT_FUNC  "osipparser2",0xB7B07141,osip_www_authenticate_get_opaque
#endif
#ifdef F_osipparser2_0263
	IMPORT_FUNC  "osipparser2",0x6BBDF9B2,osip_www_authenticate_get_qop_options
#endif
#ifdef F_osipparser2_0264
	IMPORT_FUNC  "osipparser2",0xB3CE2E4E,osip_www_authenticate_get_realm
#endif
#ifdef F_osipparser2_0265
	IMPORT_FUNC  "osipparser2",0x8E4F759B,osip_www_authenticate_get_stale
#endif
#ifdef F_osipparser2_0266
	IMPORT_FUNC  "osipparser2",0xC4DD609E,osip_www_authenticate_init
#endif
#ifdef F_osipparser2_0267
	IMPORT_FUNC  "osipparser2",0x9A55B88D,osip_www_authenticate_parse
#endif
#ifdef F_osipparser2_0268
	IMPORT_FUNC  "osipparser2",0x216BAECC,osip_www_authenticate_set_algorithm
#endif
#ifdef F_osipparser2_0269
	IMPORT_FUNC  "osipparser2",0x982B303A,osip_www_authenticate_set_auth_type
#endif
#ifdef F_osipparser2_0270
	IMPORT_FUNC  "osipparser2",0xAA88E1DA,osip_www_authenticate_set_domain
#endif
#ifdef F_osipparser2_0271
	IMPORT_FUNC  "osipparser2",0xD485A001,osip_www_authenticate_set_nonce
#endif
#ifdef F_osipparser2_0272
	IMPORT_FUNC  "osipparser2",0x8D6DC057,osip_www_authenticate_set_opaque
#endif
#ifdef F_osipparser2_0273
	IMPORT_FUNC  "osipparser2",0x1CA7DFF0,osip_www_authenticate_set_qop_options
#endif
#ifdef F_osipparser2_0274
	IMPORT_FUNC  "osipparser2",0x84CE13E3,osip_www_authenticate_set_realm
#endif
#ifdef F_osipparser2_0275
	IMPORT_FUNC  "osipparser2",0x0A95A121,osip_www_authenticate_set_stale
#endif
#ifdef F_osipparser2_0276
	IMPORT_FUNC  "osipparser2",0x5453ACDB,osip_www_authenticate_to_str
#endif
#ifdef F_osipparser2_0277
	IMPORT_FUNC  "osipparser2",0xF827A9FA,sdp_attribute_free
#endif
#ifdef F_osipparser2_0278
	IMPORT_FUNC  "osipparser2",0xEA2D9320,sdp_attribute_init
#endif
#ifdef F_osipparser2_0279
	IMPORT_FUNC  "osipparser2",0x9DF0068A,sdp_bandwidth_free
#endif
#ifdef F_osipparser2_0280
	IMPORT_FUNC  "osipparser2",0x28BAE05E,sdp_bandwidth_init
#endif
#ifdef F_osipparser2_0281
	IMPORT_FUNC  "osipparser2",0x838B1721,sdp_connection_free
#endif
#ifdef F_osipparser2_0282
	IMPORT_FUNC  "osipparser2",0xCC85D2FD,sdp_connection_init
#endif
#ifdef F_osipparser2_0283
	IMPORT_FUNC  "osipparser2",0x86BB2B1C,sdp_message_e_email_get
#endif
#ifdef F_osipparser2_0284
	IMPORT_FUNC  "osipparser2",0x1D004B2E,sdp_key_free
#endif
#ifdef F_osipparser2_0285
	IMPORT_FUNC  "osipparser2",0x047E74D5,sdp_key_init
#endif
#ifdef F_osipparser2_0286
	IMPORT_FUNC  "osipparser2",0x937616F3,sdp_media_free
#endif
#ifdef F_osipparser2_0287
	IMPORT_FUNC  "osipparser2",0xA4F76B19,sdp_media_init
#endif
#ifdef F_osipparser2_0288
	IMPORT_FUNC  "osipparser2",0x6F71C3AE,sdp_message_a_att_field_get
#endif
#ifdef F_osipparser2_0289
	IMPORT_FUNC  "osipparser2",0x01AE3BF1,sdp_message_a_att_value_get
#endif
#ifdef F_osipparser2_0290
	IMPORT_FUNC  "osipparser2",0xD35D9F61,sdp_message_a_attribute_add
#endif
#ifdef F_osipparser2_0291
	IMPORT_FUNC  "osipparser2",0x3E16851C,sdp_message_attribute_get
#endif
#ifdef F_osipparser2_0292
	IMPORT_FUNC  "osipparser2",0x1116D39D,sdp_message_b_bandwidth_add
#endif
#ifdef F_osipparser2_0293
	IMPORT_FUNC  "osipparser2",0x6F180554,sdp_message_b_bandwidth_get
#endif
#ifdef F_osipparser2_0294
	IMPORT_FUNC  "osipparser2",0xE584E5F2,sdp_message_b_bwtype_get
#endif
#ifdef F_osipparser2_0295
	IMPORT_FUNC  "osipparser2",0x8E36DEA0,sdp_message_bandwidth_get
#endif
#ifdef F_osipparser2_0296
	IMPORT_FUNC  "osipparser2",0x6CAF4F34,sdp_message_c_addr_get
#endif
#ifdef F_osipparser2_0297
	IMPORT_FUNC  "osipparser2",0xA71466E0,sdp_message_c_addr_multicast_int_get
#endif
#ifdef F_osipparser2_0298
	IMPORT_FUNC  "osipparser2",0x992B396C,sdp_message_c_addr_multicast_ttl_get
#endif
#ifdef F_osipparser2_0299
	IMPORT_FUNC  "osipparser2",0x96E13D92,sdp_message_c_addrtype_get
#endif
#ifdef F_osipparser2_0300
	IMPORT_FUNC  "osipparser2",0x9771FFC9,sdp_message_c_connection_add
#endif
#ifdef F_osipparser2_0301
	IMPORT_FUNC  "osipparser2",0xE05807C1,sdp_message_c_nettype_get
#endif
#ifdef F_osipparser2_0302
	IMPORT_FUNC  "osipparser2",0x4D706C57,sdp_message_clone
#endif
#ifdef F_osipparser2_0303
	IMPORT_FUNC  "osipparser2",0xAB6B8294,sdp_message_connection_get
#endif
#ifdef F_osipparser2_0304
	IMPORT_FUNC  "osipparser2",0x6782982A,sdp_message_e_email_add
#endif
#ifdef F_osipparser2_0305
	IMPORT_FUNC  "osipparser2",0x65BF9CA0,sdp_message_endof_media
#endif
#ifdef F_osipparser2_0306
	IMPORT_FUNC  "osipparser2",0x581BD875,sdp_message_free
#endif
#ifdef F_osipparser2_0307
	IMPORT_FUNC  "osipparser2",0xC5A13A99,sdp_message_i_info_get
#endif
#ifdef F_osipparser2_0308
	IMPORT_FUNC  "osipparser2",0x388E379A,sdp_message_i_info_set
#endif
#ifdef F_osipparser2_0309
	IMPORT_FUNC  "osipparser2",0xEF89D6CB,sdp_message_init
#endif
#ifdef F_osipparser2_0310
	IMPORT_FUNC  "osipparser2",0xE47B989C,sdp_message_k_key_set
#endif
#ifdef F_osipparser2_0311
	IMPORT_FUNC  "osipparser2",0xA9D1912E,sdp_message_k_keydata_get
#endif
#ifdef F_osipparser2_0312
	IMPORT_FUNC  "osipparser2",0x161D37CF,sdp_message_k_keytype_get
#endif
#ifdef F_osipparser2_0313
	IMPORT_FUNC  "osipparser2",0xBF6256C3,sdp_message_m_media_add
#endif
#ifdef F_osipparser2_0314
	IMPORT_FUNC  "osipparser2",0x2AD3EE45,sdp_message_m_media_get
#endif
#ifdef F_osipparser2_0315
	IMPORT_FUNC  "osipparser2",0x153F8151,sdp_message_m_number_of_port_get
#endif
#ifdef F_osipparser2_0316
	IMPORT_FUNC  "osipparser2",0xF4C037B5,sdp_message_m_payload_add
#endif
#ifdef F_osipparser2_0317
	IMPORT_FUNC  "osipparser2",0x30127A6E,sdp_message_m_payload_get
#endif
#ifdef F_osipparser2_0318
	IMPORT_FUNC  "osipparser2",0x0F8098C9,sdp_message_m_port_get
#endif
#ifdef F_osipparser2_0319
	IMPORT_FUNC  "osipparser2",0x30BB2853,sdp_message_m_proto_get
#endif
#ifdef F_osipparser2_0320
	IMPORT_FUNC  "osipparser2",0x82AA0D6D,sdp_message_o_addr_get
#endif
#ifdef F_osipparser2_0321
	IMPORT_FUNC  "osipparser2",0x8AC31B8A,sdp_message_o_addrtype_get
#endif
#ifdef F_osipparser2_0322
	IMPORT_FUNC  "osipparser2",0xB4EFC434,sdp_message_o_nettype_get
#endif
#ifdef F_osipparser2_0323
	IMPORT_FUNC  "osipparser2",0x8E3D9A35,sdp_message_o_origin_set
#endif
#ifdef F_osipparser2_0324
	IMPORT_FUNC  "osipparser2",0xFD2A08FD,sdp_message_o_sess_id_get
#endif
#ifdef F_osipparser2_0325
	IMPORT_FUNC  "osipparser2",0x79D1C819,sdp_message_o_sess_version_get
#endif
#ifdef F_osipparser2_0326
	IMPORT_FUNC  "osipparser2",0xCE19CEBC,sdp_message_o_username_get
#endif
#ifdef F_osipparser2_0327
	IMPORT_FUNC  "osipparser2",0x35D71C8B,sdp_message_p_phone_add
#endif
#ifdef F_osipparser2_0328
	IMPORT_FUNC  "osipparser2",0x699E265C,sdp_message_p_phone_get
#endif
#ifdef F_osipparser2_0329
	IMPORT_FUNC  "osipparser2",0x0F48B40D,sdp_message_parse
#endif
#ifdef F_osipparser2_0330
	IMPORT_FUNC  "osipparser2",0x03C1B69A,sdp_message_r_repeat_add
#endif
#ifdef F_osipparser2_0331
	IMPORT_FUNC  "osipparser2",0x6A112784,sdp_message_r_repeat_get
#endif
#ifdef F_osipparser2_0332
	IMPORT_FUNC  "osipparser2",0x0E491279,sdp_message_s_name_get
#endif
#ifdef F_osipparser2_0333
	IMPORT_FUNC  "osipparser2",0xEC05B615,sdp_message_s_name_set
#endif
#ifdef F_osipparser2_0334
	IMPORT_FUNC  "osipparser2",0x1E9C13C3,sdp_message_t_start_time_get
#endif
#ifdef F_osipparser2_0335
	IMPORT_FUNC  "osipparser2",0x949BF078,sdp_message_t_stop_time_get
#endif
#ifdef F_osipparser2_0336
	IMPORT_FUNC  "osipparser2",0x2509B97C,sdp_message_t_time_descr_add
#endif
#ifdef F_osipparser2_0337
	IMPORT_FUNC  "osipparser2",0x4BC8C54B,sdp_message_to_str
#endif
#ifdef F_osipparser2_0338
	IMPORT_FUNC  "osipparser2",0x57B448C2,sdp_message_u_uri_get
#endif
#ifdef F_osipparser2_0339
	IMPORT_FUNC  "osipparser2",0x88DF22DB,sdp_message_u_uri_set
#endif
#ifdef F_osipparser2_0340
	IMPORT_FUNC  "osipparser2",0x111EE872,sdp_message_v_version_get
#endif
#ifdef F_osipparser2_0341
	IMPORT_FUNC  "osipparser2",0x85C0D1D1,sdp_message_v_version_set
#endif
#ifdef F_osipparser2_0342
	IMPORT_FUNC  "osipparser2",0x560E0F50,sdp_message_z_adjustments_get
#endif
#ifdef F_osipparser2_0343
	IMPORT_FUNC  "osipparser2",0x98D36395,sdp_message_z_adjustments_set
#endif
#ifdef F_osipparser2_0344
	IMPORT_FUNC  "osipparser2",0xAD9ABFDC,sdp_time_descr_free
#endif
#ifdef F_osipparser2_0345
	IMPORT_FUNC  "osipparser2",0x38F1DD89,sdp_time_descr_init
#endif
#ifdef F_osipparser2_0346
	IMPORT_FUNC  "osipparser2",0xA274E13B,via_get_comment
#endif
#ifdef F_osipparser2_0347
	IMPORT_FUNC  "osipparser2",0x7C77CCF1,via_get_host
#endif
#ifdef F_osipparser2_0348
	IMPORT_FUNC  "osipparser2",0x435F6C30,via_get_port
#endif
#ifdef F_osipparser2_0349
	IMPORT_FUNC  "osipparser2",0x5898A726,via_get_protocol
#endif
#ifdef F_osipparser2_0350
	IMPORT_FUNC  "osipparser2",0xD97377CC,via_get_version
#endif
#ifdef F_osipparser2_0351
	IMPORT_FUNC  "osipparser2",0xCB901AFE,via_set_comment
#endif
#ifdef F_osipparser2_0352
	IMPORT_FUNC  "osipparser2",0xE567358F,via_set_host
#endif
#ifdef F_osipparser2_0353
	IMPORT_FUNC  "osipparser2",0x6CC2BEEF,via_set_port
#endif
#ifdef F_osipparser2_0354
	IMPORT_FUNC  "osipparser2",0xE75F1380,via_set_protocol
#endif
#ifdef F_osipparser2_0355
	IMPORT_FUNC  "osipparser2",0x533382B3,via_set_version
#endif
#ifdef F_osipparser2_0356
	IMPORT_FUNC  "osipparser2",0x675C6377,MD5Update
#endif
#ifdef F_osipparser2_0357
	IMPORT_FUNC  "osipparser2",0x05829DA2,MD5Final
#endif
#ifdef F_osipparser2_0358
	IMPORT_FUNC  "osipparser2",0x833503A1,MD5Init
#endif
#ifdef F_osipparser2_0359
	IMPORT_FUNC  "osipparser2",0xF53AA5F1,osip_enquote
#endif
#ifdef F_osipparser2_0360
	IMPORT_FUNC  "osipparser2",0xAFABC64D,osip_dequote
#endif
#ifdef F_osipparser2_0361
	IMPORT_FUNC  "osipparser2",0x8F6CCBF1,osip_authentication_info_init
#endif
#ifdef F_osipparser2_0362
	IMPORT_FUNC  "osipparser2",0x15958DDB,osip_authentication_info_parse
#endif
#ifdef F_osipparser2_0363
	IMPORT_FUNC  "osipparser2",0x5BE20AB0,osip_authentication_info_to_str
#endif
#ifdef F_osipparser2_0364
	IMPORT_FUNC  "osipparser2",0x40DE4969,osip_authentication_info_free
#endif
#ifdef F_osipparser2_0365
	IMPORT_FUNC  "osipparser2",0x41105CC0,osip_authentication_info_clone
#endif
#ifdef F_osipparser2_0366
	IMPORT_FUNC  "osipparser2",0x5F97CFF8,osip_authentication_info_get_nextnonce
#endif
#ifdef F_osipparser2_0367
	IMPORT_FUNC  "osipparser2",0x5FAB95D4,osip_authentication_info_set_nextnonce
#endif
#ifdef F_osipparser2_0368
	IMPORT_FUNC  "osipparser2",0xE0956A15,osip_authentication_info_get_cnonce
#endif
#ifdef F_osipparser2_0369
	IMPORT_FUNC  "osipparser2",0x96E95EF5,osip_authentication_info_set_cnonce
#endif
#ifdef F_osipparser2_0370
	IMPORT_FUNC  "osipparser2",0x535B533C,osip_authentication_info_get_qop_options
#endif
#ifdef F_osipparser2_0371
	IMPORT_FUNC  "osipparser2",0x9273090E,osip_authentication_info_set_qop_options
#endif
#ifdef F_osipparser2_0372
	IMPORT_FUNC  "osipparser2",0x8D28FF7D,osip_authentication_info_get_rspauth
#endif
#ifdef F_osipparser2_0373
	IMPORT_FUNC  "osipparser2",0xFE21C8A3,osip_authentication_info_set_rspauth
#endif
#ifdef F_osipparser2_0374
	IMPORT_FUNC  "osipparser2",0x0ECB5F77,osip_authentication_info_get_nonce_count
#endif
#ifdef F_osipparser2_0375
	IMPORT_FUNC  "osipparser2",0x44D600CB,osip_authentication_info_set_nonce_count
#endif
#ifdef F_osipparser2_0376
	IMPORT_FUNC  "osipparser2",0x3E1DCCA5,osip_message_set_authentication_info
#endif
#ifdef F_osipparser2_0377
	IMPORT_FUNC  "osipparser2",0xF9347ECE,osip_message_get_authentication_info
#endif
#ifdef F_osipparser2_0378
	IMPORT_FUNC  "osipparser2",0x3352CD13,osip_message_set_proxy_authentication_info
#endif
#ifdef F_osipparser2_0379
	IMPORT_FUNC  "osipparser2",0x053A6547,osip_message_get_proxy_authentication_info
#endif
#ifdef F_osipparser2_0380
	IMPORT_FUNC  "osipparser2",0xD0804C24,osip_list_iterator_remove
#endif
#ifdef F_osipparser2_0381
	IMPORT_FUNC  "osipparser2",0x81F21A75,osip_list_get_next
#endif
#ifdef F_osipparser2_0382
	IMPORT_FUNC  "osipparser2",0x44408789,osip_list_get_first
#endif
#ifdef F_osipparser2_0383
	IMPORT_FUNC  "osipparser2",0xEF1BA87E,osip_message_set_multiple_header
#endif
