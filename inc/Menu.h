#ifndef __MENU_H
#define __MENU_H

/**	������ ����
 * 	�� ������ ������ ����� ������� ���������� ������� ���������/��������� ����������
 * 	� �� ����������.
 */
enum eMENUlvl {
    LVL_START = 1, // 1
    LVL_MENU, // 2
    LVL_DATA_TIME, // 3
    LVL_JOURNAL, // 4
    LVL_SETUP, // 5
    LVL_PARAM_VIEW, // 6
    LVL_DEF_VIEW, // 7
    LVL_PRM_VIEW, // 8
    LVL_PRD_VIEW, // 9
    LVL_GLB_VIEW, // 10
    LVL_REGIME, // 11
    LVL_PARAM_SETUP, // 12
    LVL_DEF_SETUP, // 13
    LVL_PRM_SETUP, // 14
    LVL_PRD_SETUP, // 15
    LVL_GLB_SETUP, // 16
    LVL_NO, // 17
    LVL_PROTOCOL, // 18
    LVL_INFO, // 19
    LVL_TEST, // 20
    LVL_JRN_VIEW, // 21
    LVL_UPR, // 22
    LVL_AC // 23
};

/** ������ ���� ����������
 * 	������ ��������� � __flash unsigned __flash char* Menu22upr[]
 */
enum eMENUctrlName {
    CTRL_NAME_RESET_SELF = 0,
    CTRL_NAME_RESET_REMOTE,
    CTRL_NAME_RESET_REMOTE_1,
    CTRL_NAME_RESET_REMOTE_2,
    CTRL_NAME_RESET_REMOTE_3,
    CTRL_NAME_START_REMOTE,
    CTRL_NAME_START_REMOTE_1,
    CTRL_NAME_START_REMOTE_2,
    CTRL_NAME_START_REMOTE_3,
    CTRL_NAME_START_REMOTE_12,
    CTRL_NAME_AC_AUTO,
    CTRL_NAME_AC_ACCELERATED,
    CTRL_NAME_AC_OFF,
    CTRL_NAME_AC_CHECK,
    CTRL_NAME_AC_TEST,
    CTRL_NAME_AC_START,
    CTRL_NAME_CALL,
    CTRL_NAME_AC_NORMAL,
    CTRL_NAME_AC_QUICK,
    CTRL_NAME_START_REMOTE_MAN,
    CTRL_NAME_AC_ONE_SIDE,
    CTRL_NAME_AC_RESET,
    CTRL_NAME_AC_START_SELF,
    CTRL_NAME_AC_START_REMOTE,
    CTRL_NAME_START_PRD,
    CTRL_NAME_START_ON,
    CTRL_NAME_START_OFF,
    CTRL_NAME_REMOTE_MAN_1,
    CTRL_NAME_REMOTE_MAN_2,
    CTRL_NAME_REMOTE_MAN_3,
    CTRL_NAME_REMOTE_MAN_12,
    CTRL_NAME_START_REMOTE_4,
    CTRL_NAME_REMOTE_MAN_4,
    CTRL_NAME_AC_REQUEST
};

/** ��� ������� � ���� ����������
 */
enum eMENUctrlCom {
    // ������� ��� 0 , ���. ������������ 0x0A
    CTRL_COM_AC_AUTO_ACCELERATED = 1,
    CTRL_COM_AC_AUTO_NORMAL, // 2
    CTRL_COM_AC_ACCELERATED, // 3
    CTRL_COM_AC_OFF, // 4
    CTRL_COM_AC_CHECK, // 5
    CTRL_COM_AC_TEST, // 6
    CTRL_COM_AC_START, // 7

    // ������� ��� 1, ���. ���������� 0x72
    CTRL_COM_RESET_SELF = 0x81,
    CTRL_COM_RESET_REMOTE, // 2
    CTRL_COM_RESET_REMOTE_2, // 3
    CTRL_COM_START_REMOTE, // 4
    CTRL_COM_START_REMOTE_2, // 5
    CTRL_COM_START_REMOTE_12, // 6
    CTRL_COM_CALL, // 7
    CTRL_COM_START_ON, // 8
    CTRL_COM_START_OFF, // 9
    CTRL_COM_MAN_REMOTE_1, // 10
    CTRL_COM_MAN_REMOTE_2, // 11
    CTRL_COM_MAN_REMOTE_12, // 12
    CTRL_COM_START_REMOTE_3, // 13
    CTRL_COM_MAN_REMOTE_3, // 14
    CTRL_COM_AC_RESET // 15
};

/** ����� �������� �������� (!!! ������ ��������� � �������� Menu20gr !!!)
 */
enum eMENUtestSignals {
    SIGN_ERROR = 0,
    SIGN_OFF, // ��� �������
    SIGN_DEF,
    SIGN_CF1,
    SIGN_CF2,
    SIGN_CF3,
    SIGN_CF4,
    SIGN_COM1,
    SIGN_COM2,
    SIGN_COM3,
    SIGN_COM4,
    SIGN_COM5,
    SIGN_COM6,
    SIGN_COM7,
    SIGN_COM8,
    SIGN_COM9,
    SIGN_COM10,
    SIGN_COM11,
    SIGN_COM12,
    SIGN_COM13,
    SIGN_COM14,
    SIGN_COM15,
    SIGN_COM16,
    SIGN_COM17,
    SIGN_COM18,
    SIGN_COM19,
    SIGN_COM20,
    SIGN_COM21,
    SIGN_COM22,
    SIGN_COM23,
    SIGN_COM24,
    SIGN_COM25,
    SIGN_COM26,
    SIGN_COM27,
    SIGN_COM28,
    SIGN_COM29,
    SIGN_COM30,
    SIGN_COM31,
    SIGN_COM32
};

#endif
