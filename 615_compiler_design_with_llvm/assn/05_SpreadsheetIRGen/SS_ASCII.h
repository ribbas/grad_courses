// SS_ASCII.h
// by Allyn Shell
// Feb 2018

#ifndef SS_ASCII_H_
#define SS_ASCII_H_

// The 6 character categories in the ASCII alphabet are:
enum categ {
	WS,  // 0  White Space
	CON, // 1  Control Characters
	SYM, // 2  Special Symbols
	DGT, // 3  Numeric Digit
	UC,  // 4  Upper Case Alpha
	LC   // 5  Lower Case Alpha
};

// The ASCII table maps the characters of
// the ASCII alphabet into their categories.
const char ASCII[] = {
		0x01, // 0x00 = NUL
		0x01, // 0x01 = SOH
		0x01, // 0x02 = STX
		0x01, // 0x03 = ETX
		0x01, // 0x04 = EOT
		0x01, // 0x05 = ENQ
		0x01, // 0x06 = ACK
		0x01, // 0x07 = BEL
		0x01, // 0x08 = BS
		0x00, // 0x09 = TAB
		0x00, // 0x0A = LF
		0x00, // 0x0B = VT
		0x00, // 0x0C = FF
		0x00, // 0x0D = CR
		0x01, // 0x0E = SO
		0x01, // 0x0F = SI

		0x01, // 0x10 = DEL
		0x01, // 0x11 = DC1
		0x01, // 0x12 = DC2
		0x01, // 0x13 = DC3
		0x01, // 0x14 = DC4
		0x01, // 0x15 = NAK
		0x01, // 0x16 = SYN
		0x01, // 0x17 = ETB
		0x01, // 0x18 = CAN
		0x01, // 0x19 = EM
		0x01, // 0x1A = SUB
		0x01, // 0x1B = ESC
		0x01, // 0x1C = FS
		0x01, // 0x1D = GS
		0x01, // 0x1E = RS
		0x01, // 0x1F = US

		0x00, // 0x20 = �   �
		0x02, // 0x21 = � ! �
		0x02, // 0x22 = � � �
		0x02, // 0x23 = � # �
		0x02, // 0x24 = � $ �
		0x02, // 0x25 = � % �
		0x02, // 0x26 = � & �
		0x02, // 0x27 = � � �
		0x02, // 0x28 = � ( �
		0x02, // 0x29 = � ) �
		0x02, // 0x2A = � * �
		0x02, // 0x2B = � + �
		0x02, // 0x2C = � , �
		0x02, // 0x2D = � � �
		0x02, // 0x2E = � . �
		0x02, // 0x2F = � / �

		0x03, // 0x30 = � 0 �
		0x03, // 0x31 = � 1 �
		0x03, // 0x32 = � 2 �
		0x03, // 0x33 = � 3 �
		0x03, // 0x34 = � 4 �
		0x03, // 0x35 = � 5 �
		0x03, // 0x36 = � 6 �
		0x03, // 0x37 = � 7 �
		0x03, // 0x38 = � 8 �
		0x03, // 0x39 = � 9 �
		0x02, // 0x3A = � : �
		0x02, // 0x3B = � ; �
		0x02, // 0x3C = � < �
		0x02, // 0x3D = � = �
		0x02, // 0x3E = � > �
		0x02, // 0x3F = � ? �

		0x02, // 0x40 = � @ �
		0x04, // 0x41 = � A �
		0x04, // 0x42 = � B �
		0x04, // 0x43 = � C �
		0x04, // 0x44 = � D �
		0x04, // 0x45 = � E �
		0x04, // 0x46 = � F �
		0x04, // 0x47 = � G �
		0x04, // 0x48 = � H �
		0x04, // 0x49 = � I �
		0x04, // 0x4A = � J �
		0x04, // 0x4B = � K �
		0x04, // 0x4C = � L �
		0x04, // 0x4D = � M �
		0x04, // 0x4E = � N �
		0x04, // 0x4F = � O �

		0x04, // 0x50 = � P �
		0x04, // 0x51 = � Q �
		0x04, // 0x52 = � R �
		0x04, // 0x53 = � S �
		0x04, // 0x54 = � T �
		0x04, // 0x55 = � U �
		0x04, // 0x56 = � V �
		0x04, // 0x57 = � W �
		0x04, // 0x58 = � X �
		0x04, // 0x59 = � Y �
		0x04, // 0x5A = � Z �
		0x02, // 0x5B = � [ �
		0x02, // 0x5C = � \ �
		0x02, // 0x5D = � ] �
		0x02, // 0x5E = � ^ �
		0x02, // 0x5F = � _ �

		0x02, // 0x60 = � ` �
		0x05, // 0x61 = � a �
		0x05, // 0x62 = � b �
		0x05, // 0x63 = � c �
		0x05, // 0x64 = � d �
		0x05, // 0x65 = � e �
		0x05, // 0x66 = � f �
		0x05, // 0x67 = � g �
		0x05, // 0x68 = � h �
		0x05, // 0x69 = � i �
		0x05, // 0x6A = � j �
		0x05, // 0x6B = � k �
		0x05, // 0x6C = � l �
		0x05, // 0x6D = � m �
		0x05, // 0x6E = � n �
		0x05, // 0x6F = � o �

		0x05, // 0x70 = � p �
		0x05, // 0x71 = � q �
		0x05, // 0x72 = � r �
		0x05, // 0x73 = � s �
		0x05, // 0x74 = � t �
		0x05, // 0x75 = � u �
		0x05, // 0x76 = � v �
		0x05, // 0x77 = � w �
		0x05, // 0x78 = � x �
		0x05, // 0x79 = � y �
		0x05, // 0x7A = � z �
		0x02, // 0x7B = � { �
		0x02, // 0x7C = � | �
		0x02, // 0x7D = � } �
		0x02, // 0x7E = � ~ �
		0x02  // 0x7F = RBT
};

#endif // SS_ASCII_H_
