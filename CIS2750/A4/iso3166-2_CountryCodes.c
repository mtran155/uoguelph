/******************************************************************************
 * FILE NAME: iso3166-2_CountryCodes.c
 * PURPOSE:
 * AUTHOR: Przemyslaw Gawron
 * CREATED: Thursday, February 6, 2014
 * CONTACT: pgawron@uoguelph.ca
 * NOTE: Created for Assignment2 of cis2750 at the University of Guelph
 ******************************************************************************/

#define _GNU_SOURCE
#include "iso3166-2_CountryCodes.h"
#include <string.h>

char *countryToCode(char *country){
    char *countryCode = NULL;
    if(strcasecmp("AFGHANISTAN",country) == 0){
        countryCode = ("AF");
        return countryCode;
    }else if(strcasecmp("ÅLAND ISLANDS",country) == 0){
        countryCode = ("AX");
        return countryCode;
    }else if(strcasecmp("ALBANIA",country) == 0){
        countryCode = ("AL");
        return countryCode;
    }else if(strcasecmp("ALGERIA",country) == 0){
        countryCode = ("DZ");
        return countryCode;
    }else if(strcasecmp("AMERICAN SAMOA",country) == 0){
        countryCode = ("AS");
        return countryCode;
    }else if(strcasecmp("ANDORRA",country) == 0){
        countryCode = ("AD");
        return countryCode;
    }else if(strcasecmp("ANGOLA",country) == 0){
        countryCode = ("AO");
        return countryCode;
    }else if(strcasecmp("ANGUILLA",country) == 0){
        countryCode = ("AI");
        return countryCode;
    }else if(strcasecmp("ANTARCTICA",country) == 0){
        countryCode = ("AQ");
        return countryCode;
    }else if(strcasecmp("ANTIGUA AND BARBUDA",country) == 0){
        countryCode = ("AG");
        return countryCode;
    }else if(strcasecmp("ARGENTINA",country) == 0){
        countryCode = ("AR");
        return countryCode;
    }else if(strcasecmp("ARMENIA",country) == 0){
        countryCode = ("AM");
        return countryCode;
    }else if(strcasecmp("ARUBA",country) == 0){
        countryCode = ("AW");
        return countryCode;
    }else if(strcasecmp("AUSTRALIA",country) == 0){
        countryCode = ("AU");
        return countryCode;
    }else if(strcasecmp("AUSTRIA",country) == 0){
        countryCode = ("AT");
        return countryCode;
    }else if(strcasecmp("AZERBAIJAN",country) == 0){
        countryCode = ("AZ");
        return countryCode;
    }else if(strcasecmp("BAHAMAS",country) == 0){
        countryCode = ("BS");
        return countryCode;
    }else if(strcasecmp("BAHRAIN",country) == 0){
        countryCode = ("BH");
        return countryCode;
    }else if(strcasecmp("BANGLADESH",country) == 0){
        countryCode = ("BD");
        return countryCode;
    }else if(strcasecmp("BARBADOS",country) == 0){
        countryCode = ("BB");
        return countryCode;
    }else if(strcasecmp("BELARUS",country) == 0){
        countryCode = ("BY");
        return countryCode;
    }else if(strcasecmp("BELGIUM",country) == 0){
        countryCode = ("BE");
        return countryCode;
    }else if(strcasecmp("BELIZE",country) == 0){
        countryCode = ("BZ");
        return countryCode;
    }else if(strcasecmp("BENIN",country) == 0){
        countryCode = ("BJ");
        return countryCode;
    }else if(strcasecmp("BERMUDA",country) == 0){
        countryCode = ("BM");
        return countryCode;
    }else if(strcasecmp("BHUTAN",country) == 0){
        countryCode = ("BT");
        return countryCode;
    }else if(strcasecmp("BOLIVIA, PLURINATIONAL STATE OF",country) == 0){
        countryCode = ("BO");
        return countryCode;
    }else if(strcasecmp("BONAIRE, SINT EUSTATIUS AND SABA",country) == 0){
        countryCode = ("BQ");
        return countryCode;
    }else if(strcasecmp("BOSNIA AND HERZEGOVINA",country) == 0){
        countryCode = ("BA");
        return countryCode;
    }else if(strcasecmp("BOTSWANA",country) == 0){
        countryCode = ("BW");
        return countryCode;
    }else if(strcasecmp("BOUVET ISLAND",country) == 0){
        countryCode = ("BV");
        return countryCode;
    }else if(strcasecmp("BRAZIL",country) == 0){
        countryCode = ("BR");
        return countryCode;
    }else if(strcasecmp("BRITISH INDIAN OCEAN TERRITORY",country) == 0){
        countryCode = ("IO");
        return countryCode;
    }else if(strcasecmp("BRUNEI DARUSSALAM",country) == 0){
        countryCode = ("BN");
        return countryCode;
    }else if(strcasecmp("BULGARIA",country) == 0){
        countryCode = ("BG");
        return countryCode;
    }else if(strcasecmp("BURKINA FASO",country) == 0){
        countryCode = ("BF");
        return countryCode;
    }else if(strcasecmp("BURUNDI",country) == 0){
        countryCode = ("BI");
        return countryCode;
    }else if(strcasecmp("CAMBODIA",country) == 0){
        countryCode = ("KH");
        return countryCode;
    }else if(strcasecmp("CAMEROON",country) == 0){
        countryCode = ("CM");
        return countryCode;
    }else if(strcasecmp("CANADA",country) == 0){
        countryCode = ("CA");
        return countryCode;
    }else if(strcasecmp("CAPE VERDE",country) == 0){
        countryCode = ("CV");
        return countryCode;
    }else if(strcasecmp("CAYMAN ISLANDS",country) == 0){
        countryCode = ("KY");
        return countryCode;
    }else if(strcasecmp("CENTRAL AFRICAN REPUBLIC",country) == 0){
        countryCode = ("CF");
        return countryCode;
    }else if(strcasecmp("CHAD",country) == 0){
        countryCode = ("TD");
        return countryCode;
    }else if(strcasecmp("CHILE",country) == 0){
        countryCode = ("CL");
        return countryCode;
    }else if(strcasecmp("CHINA",country) == 0){
        countryCode = ("CN");
        return countryCode;
    }else if(strcasecmp("CHRISTMAS ISLAND",country) == 0){
        countryCode = ("CX");
        return countryCode;
    }else if(strcasecmp("COCOS (KEELING) ISLANDS",country) == 0){
        countryCode = ("CC");
        return countryCode;
    }else if(strcasecmp("COLOMBIA",country) == 0){
        countryCode = ("CO");
        return countryCode;
    }else if(strcasecmp("COMOROS",country) == 0){
        countryCode = ("KM");
        return countryCode;
    }else if(strcasecmp("CONGO",country) == 0){
        countryCode = ("CG");
        return countryCode;
    }else if(strcasecmp("CONGO, THE DEMOCRATIC REPUBLIC OF THE",country) == 0){
        countryCode = ("CD");
        return countryCode;
    }else if(strcasecmp("COOK ISLANDS",country) == 0){
        countryCode = ("CK");
        return countryCode;
    }else if(strcasecmp("COSTA RICA",country) == 0){
        countryCode = ("CR");
        return countryCode;
    }else if(strcasecmp("CÔTE D'IVOIRE",country) == 0){
        countryCode = ("CI");
        return countryCode;
    }else if(strcasecmp("CROATIA",country) == 0){
        countryCode = ("HR");
        return countryCode;
    }else if(strcasecmp("CUBA",country) == 0){
        countryCode = ("CU");
        return countryCode;
    }else if(strcasecmp("CURAÇAO",country) == 0){
        countryCode = ("CW");
        return countryCode;
    }else if(strcasecmp("CYPRUS",country) == 0){
        countryCode = ("CY");
        return countryCode;
    }else if(strcasecmp("CZECH REPUBLIC",country) == 0){
        countryCode = ("CZ");
        return countryCode;
    }else if(strcasecmp("DENMARK",country) == 0){
        countryCode = ("DK");
        return countryCode;
    }else if(strcasecmp("DJIBOUTI",country) == 0){
        countryCode = ("DJ");
        return countryCode;
    }else if(strcasecmp("DOMINICA",country) == 0){
        countryCode = ("DM");
        return countryCode;
    }else if(strcasecmp("DOMINICAN REPUBLIC",country) == 0){
        countryCode = ("DO");
        return countryCode;
    }else if(strcasecmp("ECUADOR",country) == 0){
        countryCode = ("EC");
        return countryCode;
    }else if(strcasecmp("EGYPT",country) == 0){
        countryCode = ("EG");
        return countryCode;
    }else if(strcasecmp("EL SALVADOR",country) == 0){
        countryCode = ("SV");
        return countryCode;
    }else if(strcasecmp("EQUATORIAL GUINEA",country) == 0){
        countryCode = ("GQ");
        return countryCode;
    }else if(strcasecmp("ERITREA",country) == 0){
        countryCode = ("ER");
        return countryCode;
    }else if(strcasecmp("ESTONIA",country) == 0){
        countryCode = ("EE");
        return countryCode;
    }else if(strcasecmp("ETHIOPIA",country) == 0){
        countryCode = ("ET");
        return countryCode;
    }else if(strcasecmp("FALKLAND ISLANDS (MALVINAS)",country) == 0){
        countryCode = ("FK");
        return countryCode;
    }else if(strcasecmp("FAROE ISLANDS",country) == 0){
        countryCode = ("FO");
        return countryCode;
    }else if(strcasecmp("FIJI",country) == 0){
        countryCode = ("FJ");
        return countryCode;
    }else if(strcasecmp("FINLAND",country) == 0){
        countryCode = ("FI");
        return countryCode;
    }else if(strcasecmp("FRANCE",country) == 0){
        countryCode = ("FR");
        return countryCode;
    }else if(strcasecmp("FRENCH GUIANA",country) == 0){
        countryCode = ("GF");
        return countryCode;
    }else if(strcasecmp("FRENCH POLYNESIA",country) == 0){
        countryCode = ("PF");
        return countryCode;
    }else if(strcasecmp("FRENCH SOUTHERN TERRITORIES",country) == 0){
        countryCode = ("TF");
        return countryCode;
    }else if(strcasecmp("GABON",country) == 0){
        countryCode = ("GA");
        return countryCode;
    }else if(strcasecmp("GAMBIA",country) == 0){
        countryCode = ("GM");
        return countryCode;
    }else if(strcasecmp("GEORGIA",country) == 0){
        countryCode = ("GE");
        return countryCode;
    }else if(strcasecmp("GERMANY",country) == 0){
        countryCode = ("DE");
        return countryCode;
    }else if(strcasecmp("GHANA",country) == 0){
        countryCode = ("GH");
        return countryCode;
    }else if(strcasecmp("GIBRALTAR",country) == 0){
        countryCode = ("GI");
        return countryCode;
    }else if(strcasecmp("GREECE",country) == 0){
        countryCode = ("GR");
        return countryCode;
    }else if(strcasecmp("GREENLAND",country) == 0){
        countryCode = ("GL");
        return countryCode;
    }else if(strcasecmp("GRENADA",country) == 0){
        countryCode = ("GD");
        return countryCode;
    }else if(strcasecmp("GUADELOUPE",country) == 0){
        countryCode = ("GP");
        return countryCode;
    }else if(strcasecmp("GUAM",country) == 0){
        countryCode = ("GU");
        return countryCode;
    }else if(strcasecmp("GUATEMALA",country) == 0){
        countryCode = ("GT");
        return countryCode;
    }else if(strcasecmp("GUERNSEY",country) == 0){
        countryCode = ("GG");
        return countryCode;
    }else if(strcasecmp("GUINEA",country) == 0){
        countryCode = ("GN");
        return countryCode;
    }else if(strcasecmp("GUINEA-BISSAU",country) == 0){
        countryCode = ("GW");
        return countryCode;
    }else if(strcasecmp("GUYANA",country) == 0){
        countryCode = ("GY");
        return countryCode;
    }else if(strcasecmp("HAITI",country) == 0){
        countryCode = ("HT");
        return countryCode;
    }else if(strcasecmp("HEARD ISLAND AND MCDONALD ISLANDS",country) == 0){
        countryCode = ("HM");
        return countryCode;
    }else if(strcasecmp("HOLY SEE (VATICAN CITY STATE)",country) == 0){
        countryCode = ("VA");
        return countryCode;
    }else if(strcasecmp("HONDURAS",country) == 0){
        countryCode = ("HN");
        return countryCode;
    }else if(strcasecmp("HONG KONG",country) == 0){
        countryCode = ("HK");
        return countryCode;
    }else if(strcasecmp("HUNGARY",country) == 0){
        countryCode = ("HU");
        return countryCode;
    }else if(strcasecmp("ICELAND",country) == 0){
        countryCode = ("IS");
        return countryCode;
    }else if(strcasecmp("INDIA",country) == 0){
        countryCode = ("IN");
        return countryCode;
    }else if(strcasecmp("INDONESIA",country) == 0){
        countryCode = ("ID");
        return countryCode;
    }else if(strcasecmp("IRAN, ISLAMIC REPUBLIC OF",country) == 0){
        countryCode = ("IR");
        return countryCode;
    }else if(strcasecmp("IRAQ",country) == 0){
        countryCode = ("IQ");
        return countryCode;
    }else if(strcasecmp("IRELAND",country) == 0){
        countryCode = ("IE");
        return countryCode;
    }else if(strcasecmp("ISLE OF MAN",country) == 0){
        countryCode = ("IM");
        return countryCode;
    }else if(strcasecmp("ISRAEL",country) == 0){
        countryCode = ("IL");
        return countryCode;
    }else if(strcasecmp("ITALY",country) == 0){
        countryCode = ("IT");
        return countryCode;
    }else if(strcasecmp("JAMAICA",country) == 0){
        countryCode = ("JM");
        return countryCode;
    }else if(strcasecmp("JAPAN",country) == 0){
        countryCode = ("JP");
        return countryCode;
    }else if(strcasecmp("JERSEY",country) == 0){
        countryCode = ("JE");
        return countryCode;
    }else if(strcasecmp("JORDAN",country) == 0){
        countryCode = ("JO");
        return countryCode;
    }else if(strcasecmp("KAZAKHSTAN",country) == 0){
        countryCode = ("KZ");
        return countryCode;
    }else if(strcasecmp("KENYA",country) == 0){
        countryCode = ("KE");
        return countryCode;
    }else if(strcasecmp("KIRIBATI",country) == 0){
        countryCode = ("KI");
        return countryCode;
    }else if(strcasecmp("KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF",country) == 0){
        countryCode = ("KP");
        return countryCode;
    }else if(strcasecmp("KOREA, REPUBLIC OF",country) == 0){
        countryCode = ("KR");
        return countryCode;
    }else if (strcasecmp("south korea",country) == 0){
        countryCode = ("KR");
        return countryCode;
    }else if(strcasecmp("KUWAIT",country) == 0){
        countryCode = ("KW");
        return countryCode;
    }else if(strcasecmp("KYRGYZSTAN",country) == 0){
        countryCode = ("KG");
        return countryCode;
    }else if(strcasecmp("LAO PEOPLE'S DEMOCRATIC REPUBLIC",country) == 0){
        countryCode = ("LA");
        return countryCode;
    }else if(strcasecmp("LATVIA",country) == 0){
        countryCode = ("LV");
        return countryCode;
    }else if(strcasecmp("LEBANON",country) == 0){
        countryCode = ("LB");
        return countryCode;
    }else if(strcasecmp("LESOTHO",country) == 0){
        countryCode = ("LS");
        return countryCode;
    }else if(strcasecmp("LIBERIA",country) == 0){
        countryCode = ("LR");
        return countryCode;
    }else if(strcasecmp("LIBYA",country) == 0){
        countryCode = ("LY");
        return countryCode;
    }else if(strcasecmp("LIECHTENSTEIN",country) == 0){
        countryCode = ("LI");
        return countryCode;
    }else if(strcasecmp("LITHUANIA",country) == 0){
        countryCode = ("LT");
        return countryCode;
    }else if(strcasecmp("LUXEMBOURG",country) == 0){
        countryCode = ("LU");
        return countryCode;
    }else if(strcasecmp("MACAO",country) == 0){
        countryCode = ("MO");
        return countryCode;
    }else if(strcasecmp("MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF",country) == 0){
        countryCode = ("MK");
        return countryCode;
    }else if(strcasecmp("MADAGASCAR",country) == 0){
        countryCode = ("MG");
        return countryCode;
    }else if(strcasecmp("MALAWI",country) == 0){
        countryCode = ("MW");
        return countryCode;
    }else if(strcasecmp("MALAYSIA",country) == 0){
        countryCode = ("MY");
        return countryCode;
    }else if(strcasecmp("MALDIVES",country) == 0){
        countryCode = ("MV");
        return countryCode;
    }else if(strcasecmp("MALI",country) == 0){
        countryCode = ("ML");
        return countryCode;
    }else if(strcasecmp("MALTA",country) == 0){
        countryCode = ("MT");
        return countryCode;
    }else if(strcasecmp("MARSHALL ISLANDS",country) == 0){
        countryCode = ("MH");
        return countryCode;
    }else if(strcasecmp("MARTINIQUE",country) == 0){
        countryCode = ("MQ");
        return countryCode;
    }else if(strcasecmp("MAURITANIA",country) == 0){
        countryCode = ("MR");
        return countryCode;
    }else if(strcasecmp("MAURITIUS",country) == 0){
        countryCode = ("MU");
        return countryCode;
    }else if(strcasecmp("MAYOTTE",country) == 0){
        countryCode = ("YT");
        return countryCode;
    }else if(strcasecmp("MEXICO",country) == 0){
        countryCode = ("MX");
        return countryCode;
    }else if(strcasecmp("MICRONESIA, FEDERATED STATES OF",country) == 0){
        countryCode = ("FM");
        return countryCode;
    }else if(strcasecmp("MOLDOVA, REPUBLIC OF",country) == 0){
        countryCode = ("MD");
        return countryCode;
    }else if(strcasecmp("MONACO",country) == 0){
        countryCode = ("MC");
        return countryCode;
    }else if(strcasecmp("MONGOLIA",country) == 0){
        countryCode = ("MN");
        return countryCode;
    }else if(strcasecmp("MONTENEGRO",country) == 0){
        countryCode = ("ME");
        return countryCode;
    }else if(strcasecmp("MONTSERRAT",country) == 0){
        countryCode = ("MS");
        return countryCode;
    }else if(strcasecmp("MOROCCO",country) == 0){
        countryCode = ("MA");
        return countryCode;
    }else if(strcasecmp("MOZAMBIQUE",country) == 0){
        countryCode = ("MZ");
        return countryCode;
    }else if(strcasecmp("MYANMAR",country) == 0){
        countryCode = ("MM");
        return countryCode;
    }else if(strcasecmp("NAMIBIA",country) == 0){
        countryCode = ("NA");
        return countryCode;
    }else if(strcasecmp("NAURU",country) == 0){
        countryCode = ("NR");
        return countryCode;
    }else if(strcasecmp("NEPAL",country) == 0){
        countryCode = ("NP");
        return countryCode;
    }else if(strcasecmp("NETHERLANDS",country) == 0){
        countryCode = ("NL");
        return countryCode;
    }else if(strcasecmp("NEW CALEDONIA",country) == 0){
        countryCode = ("NC");
        return countryCode;
    }else if(strcasecmp("NEW ZEALAND",country) == 0){
        countryCode = ("NZ");
        return countryCode;
    }else if(strcasecmp("NICARAGUA",country) == 0){
        countryCode = ("NI");
        return countryCode;
    }else if(strcasecmp("NIGER",country) == 0){
        countryCode = ("NE");
        return countryCode;
    }else if(strcasecmp("NIGERIA",country) == 0){
        countryCode = ("NG");
        return countryCode;
    }else if(strcasecmp("NIUE",country) == 0){
        countryCode = ("NU");
        return countryCode;
    }else if(strcasecmp("NORFOLK ISLAND",country) == 0){
        countryCode = ("NF");
        return countryCode;
    }else if(strcasecmp("NORTHERN MARIANA ISLANDS",country) == 0){
        countryCode = ("MP");
        return countryCode;
    }else if(strcasecmp("NORWAY",country) == 0){
        countryCode = ("NO");
        return countryCode;
    }else if(strcasecmp("OMAN",country) == 0){
        countryCode = ("OM");
        return countryCode;
    }else if(strcasecmp("PAKISTAN",country) == 0){
        countryCode = ("PK");
        return countryCode;
    }else if(strcasecmp("PALAU",country) == 0){
        countryCode = ("PW");
        return countryCode;
    }else if(strcasecmp("PALESTINE, STATE OF",country) == 0){
        countryCode = ("PS");
        return countryCode;
    }else if(strcasecmp("PANAMA",country) == 0){
        countryCode = ("PA");
        return countryCode;
    }else if(strcasecmp("PAPUA NEW GUINEA",country) == 0){
        countryCode = ("PG");
        return countryCode;
    }else if(strcasecmp("PARAGUAY",country) == 0){
        countryCode = ("PY");
        return countryCode;
    }else if(strcasecmp("PERU",country) == 0){
        countryCode = ("PE");
        return countryCode;
    }else if(strcasecmp("PHILIPPINES",country) == 0){
        countryCode = ("PH");
        return countryCode;
    }else if(strcasecmp("PITCAIRN",country) == 0){
        countryCode = ("PN");
        return countryCode;
    }else if(strcasecmp("POLAND",country) == 0){
        countryCode = ("PL");
        return countryCode;
    }else if(strcasecmp("PORTUGAL",country) == 0){
        countryCode = ("PT");
        return countryCode;
    }else if(strcasecmp("PUERTO RICO",country) == 0){
        countryCode = ("PR");
        return countryCode;
    }else if(strcasecmp("QATAR",country) == 0){
        countryCode = ("QA");
        return countryCode;
    }else if(strcasecmp("RÉUNION",country) == 0){
        countryCode = ("RE");
        return countryCode;
    }else if(strcasecmp("ROMANIA",country) == 0){
        countryCode = ("RO");
        return countryCode;
    }else if(strcasecmp("RUSSIAN FEDERATION",country) == 0){
        countryCode = ("RU");
        return countryCode;
    }else if(strcasecmp("RWANDA",country) == 0){
        countryCode = ("RW");
        return countryCode;
    }else if(strcasecmp("SAINT BARTHÉLEMY",country) == 0){
        countryCode = ("BL");
        return countryCode;
    }else if(strcasecmp("SAINT HELENA, ASCENSION AND TRISTAN DA CUNHA",country) == 0){
        countryCode = ("SH");
        return countryCode;
    }else if(strcasecmp("SAINT KITTS AND NEVIS",country) == 0){
        countryCode = ("KN");
        return countryCode;
    }else if(strcasecmp("SAINT LUCIA",country) == 0){
        countryCode = ("LC");
        return countryCode;
    }else if(strcasecmp("SAINT MARTIN (FRENCH PART)",country) == 0){
        countryCode = ("MF");
        return countryCode;
    }else if(strcasecmp("SAINT PIERRE AND MIQUELON",country) == 0){
        countryCode = ("PM");
        return countryCode;
    }else if(strcasecmp("SAINT VINCENT AND THE GRENADINES",country) == 0){
        countryCode = ("VC");
        return countryCode;
    }else if(strcasecmp("SAMOA",country) == 0){
        countryCode = ("WS");
        return countryCode;
    }else if(strcasecmp("SAN MARINO",country) == 0){
        countryCode = ("SM");
        return countryCode;
    }else if(strcasecmp("SAO TOME AND PRINCIPE",country) == 0){
        countryCode = ("ST");
        return countryCode;
    }else if(strcasecmp("SAUDI ARABIA",country) == 0){
        countryCode = ("SA");
        return countryCode;
    }else if(strcasecmp("SENEGAL",country) == 0){
        countryCode = ("SN");
        return countryCode;
    }else if(strcasecmp("SERBIA",country) == 0){
        countryCode = ("RS");
        return countryCode;
    }else if(strcasecmp("SEYCHELLES",country) == 0){
        countryCode = ("SC");
        return countryCode;
    }else if(strcasecmp("SIERRA LEONE",country) == 0){
        countryCode = ("SL");
        return countryCode;
    }else if(strcasecmp("SINGAPORE",country) == 0){
        countryCode = ("SG");
        return countryCode;
    }else if(strcasecmp("SINT MAARTEN (DUTCH PART)",country) == 0){
        countryCode = ("SX");
        return countryCode;
    }else if(strcasecmp("SLOVAKIA",country) == 0){
        countryCode = ("SK");
        return countryCode;
    }else if(strcasecmp("SLOVENIA",country) == 0){
        countryCode = ("SI");
        return countryCode;
    }else if(strcasecmp("SOLOMON ISLANDS",country) == 0){
        countryCode = ("SB");
        return countryCode;
    }else if(strcasecmp("SOMALIA",country) == 0){
        countryCode = ("SO");
        return countryCode;
    }else if(strcasecmp("SOUTH AFRICA",country) == 0){
        countryCode = ("ZA");
        return countryCode;
    }else if(strcasecmp("SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS",country) == 0){
        countryCode = ("GS");
        return countryCode;
    }else if(strcasecmp("SOUTH SUDAN",country) == 0){
        countryCode = ("SS");
        return countryCode;
    }else if(strcasecmp("SPAIN",country) == 0){
        countryCode = ("ES");
        return countryCode;
    }else if(strcasecmp("SRI LANKA",country) == 0){
        countryCode = ("LK");
        return countryCode;
    }else if(strcasecmp("SUDAN",country) == 0){
        countryCode = ("SD");
        return countryCode;
    }else if(strcasecmp("SURINAME",country) == 0){
        countryCode = ("SR");
        return countryCode;
    }else if(strcasecmp("SVALBARD AND JAN MAYEN",country) == 0){
        countryCode = ("SJ");
        return countryCode;
    }else if(strcasecmp("SWAZILAND",country) == 0){
        countryCode = ("SZ");
        return countryCode;
    }else if(strcasecmp("SWEDEN",country) == 0){
        countryCode = ("SE");
        return countryCode;
    }else if(strcasecmp("SWITZERLAND",country) == 0){
        countryCode = ("CH");
        return countryCode;
    }else if(strcasecmp("SYRIAN ARAB REPUBLIC",country) == 0){
        countryCode = ("SY");
        return countryCode;
    }else if(strcasecmp("TAIWAN, PROVINCE OF CHINA",country) == 0){
        countryCode = ("TW");
        return countryCode;
    }else if(strcasecmp("TAJIKISTAN",country) == 0){
        countryCode = ("TJ");
        return countryCode;
    }else if(strcasecmp("TANZANIA, UNITED REPUBLIC OF",country) == 0){
        countryCode = ("TZ");
        return countryCode;
    }else if(strcasecmp("THAILAND",country) == 0){
        countryCode = ("TH");
        return countryCode;
    }else if(strcasecmp("TIMOR-LESTE",country) == 0){
        countryCode = ("TL");
        return countryCode;
    }else if(strcasecmp("TOGO",country) == 0){
        countryCode = ("TG");
        return countryCode;
    }else if(strcasecmp("TOKELAU",country) == 0){
        countryCode = ("TK");
        return countryCode;
    }else if(strcasecmp("TONGA",country) == 0){
        countryCode = ("TO");
        return countryCode;
    }else if(strcasecmp("TRINIDAD AND TOBAGO",country) == 0){
        countryCode = ("TT");
        return countryCode;
    }else if(strcasecmp("TUNISIA",country) == 0){
        countryCode = ("TN");
        return countryCode;
    }else if(strcasecmp("TURKEY",country) == 0){
        countryCode = ("TR");
        return countryCode;
    }else if(strcasecmp("TURKMENISTAN",country) == 0){
        countryCode = ("TM");
        return countryCode;
    }else if(strcasecmp("TURKS AND CAICOS ISLANDS",country) == 0){
        countryCode = ("TC");
        return countryCode;
    }else if(strcasecmp("TUVALU",country) == 0){
        countryCode = ("TV");
        return countryCode;
    }else if(strcasecmp("UGANDA",country) == 0){
        countryCode = ("UG");
        return countryCode;
    }else if(strcasecmp("UKRAINE",country) == 0){
        countryCode = ("UA");
        return countryCode;
    }else if(strcasecmp("UNITED ARAB EMIRATES",country) == 0){
        countryCode = ("AE");
        return countryCode;
    }else if(strcasecmp("UNITED KINGDOM",country) == 0){
        countryCode = ("GB");
        return countryCode;
    }else if(strcasecmp("UNITED STATES",country) == 0){
        countryCode = ("US");
        return countryCode;
    }else if (strcasecmp("UNITED STATES of america",country) == 0){
        countryCode = ("US");
        return countryCode;
    }else if(strcasecmp("UNITED STATES MINOR OUTLYING ISLANDS",country) == 0){
        countryCode = ("UM");
        return countryCode;
    }else if(strcasecmp("URUGUAY",country) == 0){
        countryCode = ("UY");
        return countryCode;
    }else if(strcasecmp("UZBEKISTAN",country) == 0){
        countryCode = ("UZ");
        return countryCode;
    }else if(strcasecmp("VANUATU",country) == 0){
        countryCode = ("VU");
        return countryCode;
    }else if(strcasecmp("VENEZUELA, BOLIVARIAN REPUBLIC OF",country) == 0){
        countryCode = ("VE");
        return countryCode;
    }else if(strcasecmp("VIET NAM",country) == 0){
        countryCode = ("VN");
        return countryCode;
    }else if(strcasecmp("VIRGIN ISLANDS, BRITISH",country) == 0){
        countryCode = ("VG");
        return countryCode;
    }else if(strcasecmp("VIRGIN ISLANDS, U.S.",country) == 0){
        countryCode = ("VI");
        return countryCode;
    }else if(strcasecmp("WALLIS AND FUTUNA",country) == 0){
        countryCode = ("WF");
        return countryCode;
    }else if(strcasecmp("WESTERN SAHARA",country) == 0){
        countryCode = ("EH");
        return countryCode;
    }else if(strcasecmp("YEMEN",country) == 0){
        countryCode = ("YE");
        return countryCode;
    }else if(strcasecmp("ZAMBIA",country) == 0){
        countryCode = ("ZM");
        return countryCode;
    }else if(strcasecmp("ZIMBABWE",country) == 0){
        countryCode = ("ZW");
        return countryCode;
    }else{
        countryCode = ("");
        return countryCode;
    }
}

char *codeToCountry(char *code){
    char *country = NULL;
    
    if(strcasecmp("AF",code) == 0){
        country = ("AFGHANISTAN");
        return country;
    }else if(strcasecmp("AX",code) == 0){
        country = ("ÅLAND ISLANDS");
        return country;
    }else if(strcasecmp("AL",code) == 0){
        country = ("ALBANIA");
        return country;
    }else if(strcasecmp("DZ",code) == 0){
        country = ("ALGERIA");
        return country;
    }else if(strcasecmp("AS",code) == 0){
        country = ("AMERICAN SAMOA");
        return country;
    }else if(strcasecmp("AD",code) == 0){
        country = ("ANDORRA");
        return country;
    }else if(strcasecmp("AO",code) == 0){
        country = ("ANGOLA");
        return country;
    }else if(strcasecmp("AI",code) == 0){
        country = ("ANGUILLA");
        return country;
    }else if(strcasecmp("AQ",code) == 0){
        country = ("ANTARCTICA");
        return country;
    }else if(strcasecmp("AG",code) == 0){
        country = ("ANTIGUA AND BARBUDA");
        return country;
    }else if(strcasecmp("AR",code) == 0){
        country = ("ARGENTINA");
        return country;
    }else if(strcasecmp("AM",code) == 0){
        country = ("ARMENIA");
        return country;
    }else if(strcasecmp("AW",code) == 0){
        country = ("ARUBA");
        return country;
    }else if(strcasecmp("AU",code) == 0){
        country = ("AUSTRALIA");
        return country;
    }else if(strcasecmp("AT",code) == 0){
        country = ("AUSTRIA");
        return country;
    }else if(strcasecmp("AZ",code) == 0){
        country = ("AZERBAIJAN");
        return country;
    }else if(strcasecmp("BS",code) == 0){
        country = ("BAHAMAS");
        return country;
    }else if(strcasecmp("BH",code) == 0){
        country = ("BAHRAIN");
        return country;
    }else if(strcasecmp("BD",code) == 0){
        country = ("BANGLADESH");
        return country;
    }else if(strcasecmp("BB",code) == 0){
        country = ("BARBADOS");
        return country;
    }else if(strcasecmp("BY",code) == 0){
        country = ("BELARUS");
        return country;
    }else if(strcasecmp("BE",code) == 0){
        country = ("BELGIUM");
        return country;
    }else if(strcasecmp("BZ",code) == 0){
        country = ("BELIZE");
        return country;
    }else if(strcasecmp("BJ",code) == 0){
        country = ("BENIN");
        return country;
    }else if(strcasecmp("BM",code) == 0){
        country = ("BERMUDA");
        return country;
    }else if(strcasecmp("BT",code) == 0){
        country = ("BHUTAN");
        return country;
    }else if(strcasecmp("BO",code) == 0){
        country = ("BOLIVIA, PLURINATIONAL STATE OF");
        return country;
    }else if(strcasecmp("BQ",code) == 0){
        country = ("BONAIRE, SINT EUSTATIUS AND SABA");
        return country;
    }else if(strcasecmp("BA",code) == 0){
        country = ("BOSNIA AND HERZEGOVINA");
        return country;
    }else if(strcasecmp("BW",code) == 0){
        country = ("BOTSWANA");
        return country;
    }else if(strcasecmp("BV",code) == 0){
        country = ("BOUVET ISLAND");
        return country;
    }else if(strcasecmp("BR",code) == 0){
        country = ("BRAZIL");
        return country;
    }else if(strcasecmp("IO",code) == 0){
        country = ("BRITISH INDIAN OCEAN TERRITORY");
        return country;
    }else if(strcasecmp("BN",code) == 0){
        country = ("BRUNEI DARUSSALAM");
        return country;
    }else if(strcasecmp("BG",code) == 0){
        country = ("BULGARIA");
        return country;
    }else if(strcasecmp("BF",code) == 0){
        country = ("BURKINA FASO");
        return country;
    }else if(strcasecmp("BI",code) == 0){
        country = ("BURUNDI");
        return country;
    }else if(strcasecmp("KH",code) == 0){
        country = ("CAMBODIA");
        return country;
    }else if(strcasecmp("CM",code) == 0){
        country = ("CAMEROON");
        return country;
    }else if(strcasecmp("CA",code) == 0){
        country = ("CANADA");
        return country;
    }else if(strcasecmp("CV",code) == 0){
        country = ("CAPE VERDE");
        return country;
    }else if(strcasecmp("KY",code) == 0){
        country = ("CAYMAN ISLANDS");
        return country;
    }else if(strcasecmp("CF",code) == 0){
        country = ("CENTRAL AFRICAN REPUBLIC");
        return country;
    }else if(strcasecmp("TD",code) == 0){
        country = ("CHAD");
        return country;
    }else if(strcasecmp("CL",code) == 0){
        country = ("CHILE");
        return country;
    }else if(strcasecmp("CN",code) == 0){
        country = ("CHINA");
        return country;
    }else if(strcasecmp("CX",code) == 0){
        country = ("CHRISTMAS ISLAND");
        return country;
    }else if(strcasecmp("CC",code) == 0){
        country = ("COCOS (KEELING) ISLANDS");
        return country;
    }else if(strcasecmp("CO",code) == 0){
        country = ("COLOMBIA");
        return country;
    }else if(strcasecmp("KM",code) == 0){
        country = ("COMOROS");
        return country;
    }else if(strcasecmp("CG",code) == 0){
        country = ("CONGO");
        return country;
    }else if(strcasecmp("CD",code) == 0){
        country = ("CONGO, THE DEMOCRATIC REPUBLIC OF THE");
        return country;
    }else if(strcasecmp("CK",code) == 0){
        country = ("COOK ISLANDS");
        return country;
    }else if(strcasecmp("CR",code) == 0){
        country = ("COSTA RICA");
        return country;
    }else if(strcasecmp("CI",code) == 0){
        country = ("CÔTE D'IVOIRE");
        return country;
    }else if(strcasecmp("HR",code) == 0){
        country = ("CROATIA");
        return country;
    }else if(strcasecmp("CU",code) == 0){
        country = ("CUBA");
        return country;
    }else if(strcasecmp("CW",code) == 0){
        country = ("CURAÇAO");
        return country;
    }else if(strcasecmp("CY",code) == 0){
        country = ("CYPRUS");
        return country;
    }else if(strcasecmp("CZ",code) == 0){
        country = ("CZECH REPUBLIC");
        return country;
    }else if(strcasecmp("DK",code) == 0){
        country = ("DENMARK");
        return country;
    }else if(strcasecmp("DJ",code) == 0){
        country = ("DJIBOUTI");
        return country;
    }else if(strcasecmp("DM",code) == 0){
        country = ("DOMINICA");
        return country;
    }else if(strcasecmp("DO",code) == 0){
        country = ("DOMINICAN REPUBLIC");
        return country;
    }else if(strcasecmp("EC",code) == 0){
        country = ("ECUADOR");
        return country;
    }else if(strcasecmp("EG",code) == 0){
        country = ("EGYPT");
        return country;
    }else if(strcasecmp("SV",code) == 0){
        country = ("EL SALVADOR");
        return country;
    }else if(strcasecmp("GQ",code) == 0){
        country = ("EQUATORIAL GUINEA");
        return country;
    }else if(strcasecmp("ER",code) == 0){
        country = ("ERITREA");
        return country;
    }else if(strcasecmp("EE",code) == 0){
        country = ("ESTONIA");
        return country;
    }else if(strcasecmp("ET",code) == 0){
        country = ("ETHIOPIA");
        return country;
    }else if(strcasecmp("FK",code) == 0){
        country = ("FALKLAND ISLANDS (MALVINAS)");
        return country;
    }else if(strcasecmp("FO",code) == 0){
        country = ("FAROE ISLANDS");
        return country;
    }else if(strcasecmp("FJ",code) == 0){
        country = ("FIJI");
        return country;
    }else if(strcasecmp("FI",code) == 0){
        country = ("FINLAND");
        return country;
    }else if(strcasecmp("FR",code) == 0){
        country = ("FRANCE");
        return country;
    }else if(strcasecmp("GF",code) == 0){
        country = ("FRENCH GUIANA");
        return country;
    }else if(strcasecmp("PF",code) == 0){
        country = ("FRENCH POLYNESIA");
        return country;
    }else if(strcasecmp("TF",code) == 0){
        country = ("FRENCH SOUTHERN TERRITORIES");
        return country;
    }else if(strcasecmp("GA",code) == 0){
        country = ("GABON");
        return country;
    }else if(strcasecmp("GM",code) == 0){
        country = ("GAMBIA");
        return country;
    }else if(strcasecmp("GE",code) == 0){
        country = ("GEORGIA");
        return country;
    }else if(strcasecmp("DE",code) == 0){
        country = ("GERMANY");
        return country;
    }else if(strcasecmp("GH",code) == 0){
        country = ("GHANA");
        return country;
    }else if(strcasecmp("GI",code) == 0){
        country = ("GIBRALTAR");
        return country;
    }else if(strcasecmp("GR",code) == 0){
        country = ("GREECE");
        return country;
    }else if(strcasecmp("GL",code) == 0){
        country = ("GREENLAND");
        return country;
    }else if(strcasecmp("GD",code) == 0){
        country = ("GRENADA");
        return country;
    }else if(strcasecmp("GP",code) == 0){
        country = ("GUADELOUPE");
        return country;
    }else if(strcasecmp("GU",code) == 0){
        country = ("GUAM");
        return country;
    }else if(strcasecmp("GT",code) == 0){
        country = ("GUATEMALA");
        return country;
    }else if(strcasecmp("GG",code) == 0){
        country = ("GUERNSEY");
        return country;
    }else if(strcasecmp("GN",code) == 0){
        country = ("GUINEA");
        return country;
    }else if(strcasecmp("GW",code) == 0){
        country = ("GUINEA-BISSAU");
        return country;
    }else if(strcasecmp("GY",code) == 0){
        country = ("GUYANA");
        return country;
    }else if(strcasecmp("HT",code) == 0){
        country = ("HAITI");
        return country;
    }else if(strcasecmp("HM",code) == 0){
        country = ("HEARD ISLAND AND MCDONALD ISLANDS");
        return country;
    }else if(strcasecmp("VA",code) == 0){
        country = ("HOLY SEE (VATICAN CITY STATE)");
        return country;
    }else if(strcasecmp("HN",code) == 0){
        country = ("HONDURAS");
        return country;
    }else if(strcasecmp("HK",code) == 0){
        country = ("HONG KONG");
        return country;
    }else if(strcasecmp("HU",code) == 0){
        country = ("HUNGARY");
        return country;
    }else if(strcasecmp("IS",code) == 0){
        country = ("ICELAND");
        return country;
    }else if(strcasecmp("IN",code) == 0){
        country = ("INDIA");
        return country;
    }else if(strcasecmp("ID",code) == 0){
        country = ("INDONESIA");
        return country;
    }else if(strcasecmp("IR",code) == 0){
        country = ("IRAN, ISLAMIC REPUBLIC OF");
        return country;
    }else if(strcasecmp("IQ",code) == 0){
        country = ("IRAQ");
        return country;
    }else if(strcasecmp("IE",code) == 0){
        country = ("IRELAND");
        return country;
    }else if(strcasecmp("IM",code) == 0){
        country = ("ISLE OF MAN");
        return country;
    }else if(strcasecmp("IL",code) == 0){
        country = ("ISRAEL");
        return country;
    }else if(strcasecmp("IT",code) == 0){
        country = ("ITALY");
        return country;
    }else if(strcasecmp("JM",code) == 0){
        country = ("JAMAICA");
        return country;
    }else if(strcasecmp("JP",code) == 0){
        country = ("JAPAN");
        return country;
    }else if(strcasecmp("JE",code) == 0){
        country = ("JERSEY");
        return country;
    }else if(strcasecmp("JO",code) == 0){
        country = ("JORDAN");
        return country;
    }else if(strcasecmp("KZ",code) == 0){
        country = ("KAZAKHSTAN");
        return country;
    }else if(strcasecmp("KE",code) == 0){
        country = ("KENYA");
        return country;
    }else if(strcasecmp("KI",code) == 0){
        country = ("KIRIBATI");
        return country;
    }else if(strcasecmp("KP",code) == 0){
        country = ("KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF");
        return country;
    }else if(strcasecmp("KR",code) == 0){
        country = ("KOREA, REPUBLIC OF");
        return country;
    }else if(strcasecmp("KW",code) == 0){
        country = ("KUWAIT");
        return country;
    }else if(strcasecmp("KG",code) == 0){
        country = ("KYRGYZSTAN");
        return country;
    }else if(strcasecmp("LA",code) == 0){
        country = ("LAO PEOPLE'S DEMOCRATIC REPUBLIC");
        return country;
    }else if(strcasecmp("LV",code) == 0){
        country = ("LATVIA");
        return country;
    }else if(strcasecmp("LB",code) == 0){
        country = ("LEBANON");
        return country;
    }else if(strcasecmp("LS",code) == 0){
        country = ("LESOTHO");
        return country;
    }else if(strcasecmp("LR",code) == 0){
        country = ("LIBERIA");
        return country;
    }else if(strcasecmp("LY",code) == 0){
        country = ("LIBYA");
        return country;
    }else if(strcasecmp("LI",code) == 0){
        country = ("LIECHTENSTEIN");
        return country;
    }else if(strcasecmp("LT",code) == 0){
        country = ("LITHUANIA");
        return country;
    }else if(strcasecmp("LU",code) == 0){
        country = ("LUXEMBOURG");
        return country;
    }else if(strcasecmp("MO",code) == 0){
        country = ("MACAO");
        return country;
    }else if(strcasecmp("MK",code) == 0){
        country = ("MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF");
        return country;
    }else if(strcasecmp("MG",code) == 0){
        country = ("MADAGASCAR");
        return country;
    }else if(strcasecmp("MW",code) == 0){
        country = ("MALAWI");
        return country;
    }else if(strcasecmp("MY",code) == 0){
        country = ("MALAYSIA");
        return country;
    }else if(strcasecmp("MV",code) == 0){
        country = ("MALDIVES");
        return country;
    }else if(strcasecmp("ML",code) == 0){
        country = ("MALI");
        return country;
    }else if(strcasecmp("MT",code) == 0){
        country = ("MALTA");
        return country;
    }else if(strcasecmp("MH",code) == 0){
        country = ("MARSHALL ISLANDS");
        return country;
    }else if(strcasecmp("MQ",code) == 0){
        country = ("MARTINIQUE");
        return country;
    }else if(strcasecmp("MR",code) == 0){
        country = ("MAURITANIA");
        return country;
    }else if(strcasecmp("MU",code) == 0){
        country = ("MAURITIUS");
        return country;
    }else if(strcasecmp("YT",code) == 0){
        country = ("MAYOTTE");
        return country;
    }else if(strcasecmp("MX",code) == 0){
        country = ("MEXICO");
        return country;
    }else if(strcasecmp("FM",code) == 0){
        country = ("MICRONESIA, FEDERATED STATES OF");
        return country;
    }else if(strcasecmp("MD",code) == 0){
        country = ("MOLDOVA, REPUBLIC OF");
        return country;
    }else if(strcasecmp("MC",code) == 0){
        country = ("MONACO");
        return country;
    }else if(strcasecmp("MN",code) == 0){
        country = ("MONGOLIA");
        return country;
    }else if(strcasecmp("ME",code) == 0){
        country = ("MONTENEGRO");
        return country;
    }else if(strcasecmp("MS",code) == 0){
        country = ("MONTSERRAT");
        return country;
    }else if(strcasecmp("MA",code) == 0){
        country = ("MOROCCO");
        return country;
    }else if(strcasecmp("MZ",code) == 0){
        country = ("MOZAMBIQUE");
        return country;
    }else if(strcasecmp("MM",code) == 0){
        country = ("MYANMAR");
        return country;
    }else if(strcasecmp("NA",code) == 0){
        country = ("NAMIBIA");
        return country;
    }else if(strcasecmp("NR",code) == 0){
        country = ("NAURU");
        return country;
    }else if(strcasecmp("NP",code) == 0){
        country = ("NEPAL");
        return country;
    }else if(strcasecmp("NL",code) == 0){
        country = ("NETHERLANDS");
        return country;
    }else if(strcasecmp("NC",code) == 0){
        country = ("NEW CALEDONIA");
        return country;
    }else if(strcasecmp("NZ",code) == 0){
        country = ("NEW ZEALAND");
        return country;
    }else if(strcasecmp("NI",code) == 0){
        country = ("NICARAGUA");
        return country;
    }else if(strcasecmp("NE",code) == 0){
        country = ("NIGER");
        return country;
    }else if(strcasecmp("NG",code) == 0){
        country = ("NIGERIA");
        return country;
    }else if(strcasecmp("NU",code) == 0){
        country = ("NIUE");
        return country;
    }else if(strcasecmp("NF",code) == 0){
        country = ("NORFOLK ISLAND");
        return country;
    }else if(strcasecmp("MP",code) == 0){
        country = ("NORTHERN MARIANA ISLANDS");
        return country;
    }else if(strcasecmp("NO",code) == 0){
        country = ("NORWAY");
        return country;
    }else if(strcasecmp("OM",code) == 0){
        country = ("OMAN");
        return country;
    }else if(strcasecmp("PK",code) == 0){
        country = ("PAKISTAN");
        return country;
    }else if(strcasecmp("PW",code) == 0){
        country = ("PALAU");
        return country;
    }else if(strcasecmp("PS",code) == 0){
        country = ("PALESTINE, STATE OF");
        return country;
    }else if(strcasecmp("PA",code) == 0){
        country = ("PANAMA");
        return country;
    }else if(strcasecmp("PG",code) == 0){
        country = ("PAPUA NEW GUINEA");
        return country;
    }else if(strcasecmp("PY",code) == 0){
        country = ("PARAGUAY");
        return country;
    }else if(strcasecmp("PE",code) == 0){
        country = ("PERU");
        return country;
    }else if(strcasecmp("PH",code) == 0){
        country = ("PHILIPPINES");
        return country;
    }else if(strcasecmp("PN",code) == 0){
        country = ("PITCAIRN");
        return country;
    }else if(strcasecmp("PL",code) == 0){
        country = ("POLAND");
        return country;
    }else if(strcasecmp("PT",code) == 0){
        country = ("PORTUGAL");
        return country;
    }else if(strcasecmp("PR",code) == 0){
        country = ("PUERTO RICO");
        return country;
    }else if(strcasecmp("QA",code) == 0){
        country = ("QATAR");
        return country;
    }else if(strcasecmp("RE",code) == 0){
        country = ("RÉUNION");
        return country;
    }else if(strcasecmp("RO",code) == 0){
        country = ("ROMANIA");
        return country;
    }else if(strcasecmp("RU",code) == 0){
        country = ("RUSSIAN FEDERATION");
        return country;
    }else if(strcasecmp("RW",code) == 0){
        country = ("RWANDA");
        return country;
    }else if(strcasecmp("BL",code) == 0){
        country = ("SAINT BARTHÉLEMY");
        return country;
    }else if(strcasecmp("SH",code) == 0){
        country = ("SAINT HELENA, ASCENSION AND TRISTAN DA CUNHA");
        return country;
    }else if(strcasecmp("KN",code) == 0){
        country = ("SAINT KITTS AND NEVIS");
        return country;
    }else if(strcasecmp("LC",code) == 0){
        country = ("SAINT LUCIA");
        return country;
    }else if(strcasecmp("MF",code) == 0){
        country = ("SAINT MARTIN (FRENCH PART)");
        return country;
    }else if(strcasecmp("PM",code) == 0){
        country = ("SAINT PIERRE AND MIQUELON");
        return country;
    }else if(strcasecmp("VC",code) == 0){
        country = ("SAINT VINCENT AND THE GRENADINES");
        return country;
    }else if(strcasecmp("WS",code) == 0){
        country = ("SAMOA");
        return country;
    }else if(strcasecmp("SM",code) == 0){
        country = ("SAN MARINO");
        return country;
    }else if(strcasecmp("ST",code) == 0){
        country = ("SAO TOME AND PRINCIPE");
        return country;
    }else if(strcasecmp("SA",code) == 0){
        country = ("SAUDI ARABIA");
        return country;
    }else if(strcasecmp("SN",code) == 0){
        country = ("SENEGAL");
        return country;
    }else if(strcasecmp("RS",code) == 0){
        country = ("SERBIA");
        return country;
    }else if(strcasecmp("SC",code) == 0){
        country = ("SEYCHELLES");
        return country;
    }else if(strcasecmp("SL",code) == 0){
        country = ("SIERRA LEONE");
        return country;
    }else if(strcasecmp("SG",code) == 0){
        country = ("SINGAPORE");
        return country;
    }else if(strcasecmp("SX",code) == 0){
        country = ("SINT MAARTEN (DUTCH PART)");
        return country;
    }else if(strcasecmp("SK",code) == 0){
        country = ("SLOVAKIA");
        return country;
    }else if(strcasecmp("SI",code) == 0){
        country = ("SLOVENIA");
        return country;
    }else if(strcasecmp("SB",code) == 0){
        country = ("SOLOMON ISLANDS");
        return country;
    }else if(strcasecmp("SO",code) == 0){
        country = ("SOMALIA");
        return country;
    }else if(strcasecmp("ZA",code) == 0){
        country = ("SOUTH AFRICA");
        return country;
    }else if(strcasecmp("GS",code) == 0){
        country = ("SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS");
        return country;
    }else if(strcasecmp("SS",code) == 0){
        country = ("SOUTH SUDAN");
        return country;
    }else if(strcasecmp("ES",code) == 0){
        country = ("SPAIN");
        return country;
    }else if(strcasecmp("LK",code) == 0){
        country = ("SRI LANKA");
        return country;
    }else if(strcasecmp("SD",code) == 0){
        country = ("SUDAN");
        return country;
    }else if(strcasecmp("SR",code) == 0){
        country = ("SURINAME");
        return country;
    }else if(strcasecmp("SJ",code) == 0){
        country = ("SVALBARD AND JAN MAYEN");
        return country;
    }else if(strcasecmp("SZ",code) == 0){
        country = ("SWAZILAND");
        return country;
    }else if(strcasecmp("SE",code) == 0){
        country = ("SWEDEN");
        return country;
    }else if(strcasecmp("CH",code) == 0){
        country = ("SWITZERLAND");
        return country;
    }else if(strcasecmp("SY",code) == 0){
        country = ("SYRIAN ARAB REPUBLIC");
        return country;
    }else if(strcasecmp("TW",code) == 0){
        country = ("TAIWAN, PROVINCE OF CHINA");
        return country;
    }else if(strcasecmp("TJ",code) == 0){
        country = ("TAJIKISTAN");
        return country;
    }else if(strcasecmp("TZ",code) == 0){
        country = ("TANZANIA, UNITED REPUBLIC OF");
        return country;
    }else if(strcasecmp("TH",code) == 0){
        country = ("THAILAND");
        return country;
    }else if(strcasecmp("TL",code) == 0){
        country = ("TIMOR-LESTE");
        return country;
    }else if(strcasecmp("TG",code) == 0){
        country = ("TOGO");
        return country;
    }else if(strcasecmp("TK",code) == 0){
        country = ("TOKELAU");
        return country;
    }else if(strcasecmp("TO",code) == 0){
        country = ("TONGA");
        return country;
    }else if(strcasecmp("TT",code) == 0){
        country = ("TRINIDAD AND TOBAGO");
        return country;
    }else if(strcasecmp("TN",code) == 0){
        country = ("TUNISIA");
        return country;
    }else if(strcasecmp("TR",code) == 0){
        country = ("TURKEY");
        return country;
    }else if(strcasecmp("TM",code) == 0){
        country = ("TURKMENISTAN");
        return country;
    }else if(strcasecmp("TC",code) == 0){
        country = ("TURKS AND CAICOS ISLANDS");
        return country;
    }else if(strcasecmp("TV",code) == 0){
        country = ("TUVALU");
        return country;
    }else if(strcasecmp("UG",code) == 0){
        country = ("UGANDA");
        return country;
    }else if(strcasecmp("UA",code) == 0){
        country = ("UKRAINE");
        return country;
    }else if(strcasecmp("AE",code) == 0){
        country = ("UNITED ARAB EMIRATES");
        return country;
    }else if(strcasecmp("GB",code) == 0){
        country = ("UNITED KINGDOM");
        return country;
    }else if(strcasecmp("US",code) == 0){
        country = ("UNITED STATES");
        return country;
    }else if(strcasecmp("UM",code) == 0){
        country = ("UNITED STATES MINOR OUTLYING ISLANDS");
        return country;
    }else if(strcasecmp("UY",code) == 0){
        country = ("URUGUAY");
        return country;
    }else if(strcasecmp("UZ",code) == 0){
        country = ("UZBEKISTAN");
        return country;
    }else if(strcasecmp("VU",code) == 0){
        country = ("VANUATU");
        return country;
    }else if(strcasecmp("VE",code) == 0){
        country = ("VENEZUELA, BOLIVARIAN REPUBLIC OF");
        return country;
    }else if(strcasecmp("VN",code) == 0){
        country = ("VIET NAM");
        return country;
    }else if(strcasecmp("VG",code) == 0){
        country = ("VIRGIN ISLANDS, BRITISH");
        return country;
    }else if(strcasecmp("VI",code) == 0){
        country = ("VIRGIN ISLANDS, U.S.");
        return country;
    }else if(strcasecmp("WF",code) == 0){
        country = ("WALLIS AND FUTUNA");
        return country;
    }else if(strcasecmp("EH",code) == 0){
        country = ("WESTERN SAHARA");
        return country;
    }else if(strcasecmp("YE",code) == 0){
        country = ("YEMEN");
        return country;
    }else if(strcasecmp("ZM",code) == 0){
        country = ("ZAMBIA");
        return country;
    }else if(strcasecmp("ZW",code) == 0){
        country = ("ZIMBABWE");
        return country;
    }else{
        country = ("");
        return country;
    }
}


char *provinceToCode(char *province){
    char *provinceCode = NULL;
    
    if(strcasecmp("Alberta",province) == 0){
        provinceCode = ("AB");
        return provinceCode;
    }else if(strcasecmp("British Columbia",province) == 0){
        provinceCode = ("BC");
        return provinceCode;
    }else if(strcasecmp("Manitoba",province) == 0){
        provinceCode = ("MB");
        return provinceCode;
    }else if(strcasecmp("New Brunswick",province) == 0){
        provinceCode = ("NB");
        return provinceCode;
    }else if(strcasecmp("Newfoundland and Labrador",province) == 0){
        provinceCode = ("NL");
        return provinceCode;
    }else if(strcasecmp("Nova Scotia",province) == 0){
        provinceCode = ("NS");
        return provinceCode;
    }else if(strcasecmp("Ontario",province) == 0){
        provinceCode = ("ON");
        return provinceCode;
    }else if(strcasecmp("Prince Edward Island",province) == 0){
        provinceCode = ("PE");
        return provinceCode;
    }else if(strcasecmp("Quebec",province) == 0){
        provinceCode = ("QC");
        return provinceCode;
    }else if(strcasecmp("Saskatchewan",province) == 0){
        provinceCode = ("SK");
        return provinceCode;
    }else if(strcasecmp("Northwest Territories",province) == 0){
        provinceCode = ("NT");
        return provinceCode;
    }else if(strcasecmp("Nunavut",province) == 0){
        provinceCode = ("NU");
        return provinceCode;
    }else if(strcasecmp("Yukon Territory",province) == 0){
        provinceCode = ("YT");
        return provinceCode;
    }else{
        provinceCode = ("");
        return provinceCode;
    }
}

char *codeToProvince(char *code){
    char *province = NULL;
    
    if(strcasecmp("AB",code) == 0){
        province = ("Alberta");
        return province;
    }else if(strcasecmp("BC",code) == 0){
        province = ("British Columbia");
        return province;
    }else if(strcasecmp("MB",code) == 0){
        province = ("Manitoba");
        return province;
    }else if(strcasecmp("NB",code) == 0){
        province = ("New Brunswick");
        return province;
    }else if(strcasecmp("NL",code) == 0){
        province = ("Newfoundland and Labrador");
        return province;
    }else if(strcasecmp("NS",code) == 0){
        province = ("Nova Scotia");
        return province;
    }else if(strcasecmp("ON",code) == 0){
        province = ("Ontario");
        return province;
    }else if(strcasecmp("PE",code) == 0){
        province = ("Prince Edward Island	");
        return province;
    }else if(strcasecmp("QC",code) == 0){
        province = ("Quebec");
        return province;
    }else if(strcasecmp("SK",code) == 0){
        province = ("Saskatchewan");
        return province;
    }else if(strcasecmp("NT",code) == 0){
        province = ("Northwest Territories");
        return province;
    }else if(strcasecmp("NU",code) == 0){
        province = ("Nunavut");
        return province;
    }else if(strcasecmp("YT",code) == 0){
        province = ("Yukon Territory");
        return province;
    }else{
        province = ("");
        return province;
    }
}

char *stateToCode(char *state){
    char *stateCode = NULL;
    
    if(strcasecmp("Alaska",state) == 0){
        stateCode = ("AK");
        return stateCode;
    }else if(strcasecmp("Alabama",state) == 0){
        stateCode = ("AL");
        return stateCode;
    }else if(strcasecmp("Arkansas",state) == 0){
        stateCode = ("AR");
        return stateCode;
    }else if(strcasecmp("American Samoa",state) == 0){
        stateCode = ("AS");
        return stateCode;
    }else if(strcasecmp("Arizona",state) == 0){
        stateCode = ("AZ");
        return stateCode;
    }else if(strcasecmp("California",state) == 0){
        stateCode = ("CA");
        return stateCode;
    }else if(strcasecmp("Colorado",state) == 0){
        stateCode = ("CO");
        return stateCode;
    }else if(strcasecmp("Connecticut",state) == 0){
        stateCode = ("CT");
        return stateCode;
    }else if(strcasecmp("District of Columbia",state) == 0){
        stateCode = ("DC");
        return stateCode;
    }else if(strcasecmp("Delaware",state) == 0){
        stateCode = ("DE");
        return stateCode;
    }else if(strcasecmp("Florida",state) == 0){
        stateCode = ("FL");
        return stateCode;
    }else if(strcasecmp("Georgia",state) == 0){
        stateCode = ("GA");
        return stateCode;
    }else if(strcasecmp("Guam",state) == 0){
        stateCode = ("GU");
        return stateCode;
    }else if(strcasecmp("Hawaii",state) == 0){
        stateCode = ("HI");
        return stateCode;
    }else if(strcasecmp("Iowa",state) == 0){
        stateCode = ("IA");
        return stateCode;
    }else if(strcasecmp("Idaho",state) == 0){
        stateCode = ("ID");
        return stateCode;
    }else if(strcasecmp("Illinois",state) == 0){
        stateCode = ("IL");
        return stateCode;
    }else if(strcasecmp("Indiana",state) == 0){
        stateCode = ("IN");
        return stateCode;
    }else if(strcasecmp("Kansas",state) == 0){
        stateCode = ("KS");
        return stateCode;
    }else if(strcasecmp("Kentucky",state) == 0){
        stateCode = ("KY");
        return stateCode;
    }else if(strcasecmp("Louisiana",state) == 0){
        stateCode = ("LA");
        return stateCode;
    }else if(strcasecmp("Massachusetts",state) == 0){
        stateCode = ("MA");
        return stateCode;
    }else if(strcasecmp("Maryland",state) == 0){
        stateCode = ("MD");
        return stateCode;
    }else if(strcasecmp("Maine",state) == 0){
        stateCode = ("ME");
        return stateCode;
    }else if(strcasecmp("Michigan",state) == 0){
        stateCode = ("MI");
        return stateCode;
    }else if(strcasecmp("Minnesota",state) == 0){
        stateCode = ("MN");
        return stateCode;
    }else if(strcasecmp("Missouri",state) == 0){
        stateCode = ("MO");
        return stateCode;
    }else if(strcasecmp("Northern Mariana Islands",state) == 0){
        stateCode = ("MP");
        return stateCode;
    }else if(strcasecmp("Mississippi",state) == 0){
        stateCode = ("MS");
        return stateCode;
    }else if(strcasecmp("Montana",state) == 0){
        stateCode = ("MT");
        return stateCode;
    }else if(strcasecmp("North Carolina",state) == 0){
        stateCode = ("NC");
        return stateCode;
    }else if(strcasecmp("North Dakota",state) == 0){
        stateCode = ("ND");
        return stateCode;
    }else if(strcasecmp("Nebraska",state) == 0){
        stateCode = ("NE");
        return stateCode;
    }else if(strcasecmp("New Hampshire",state) == 0){
        stateCode = ("NH");
        return stateCode;
    }else if(strcasecmp("New Jersey",state) == 0){
        stateCode = ("NJ");
        return stateCode;
    }else if(strcasecmp("New Mexico",state) == 0){
        stateCode = ("NM");
        return stateCode;
    }else if(strcasecmp("Nevada",state) == 0){
        stateCode = ("NV");
        return stateCode;
    }else if(strcasecmp("New York",state) == 0){
        stateCode = ("NY");
        return stateCode;
    }else if(strcasecmp("Ohio",state) == 0){
        stateCode = ("OH");
        return stateCode;
    }else if(strcasecmp("Oklahoma",state) == 0){
        stateCode = ("OK");
        return stateCode;
    }else if(strcasecmp("Oregon",state) == 0){
        stateCode = ("OR");
        return stateCode;
    }else if(strcasecmp("Pennsylvania",state) == 0){
        stateCode = ("PA");
        return stateCode;
    }else if(strcasecmp("Puerto Rico",state) == 0){
        stateCode = ("PR");
        return stateCode;
    }else if(strcasecmp("Rhode Island",state) == 0){
        stateCode = ("RI");
        return stateCode;
    }else if(strcasecmp("South Carolina",state) == 0){
        stateCode = ("SC");
        return stateCode;
    }else if(strcasecmp("South Dakota",state) == 0){
        stateCode = ("SD");
        return stateCode;
    }else if(strcasecmp("Tennessee",state) == 0){
        stateCode = ("TN");
        return stateCode;
    }else if(strcasecmp("Texas",state) == 0){
        stateCode = ("TX");
        return stateCode;
    }else if(strcasecmp("United States Minor Outlying Islands",state) == 0){
        stateCode = ("UM");
        return stateCode;
    }else if(strcasecmp("Utah",state) == 0){
        stateCode = ("UT");
        return stateCode;
    }else if(strcasecmp("Virginia",state) == 0){
        stateCode = ("VA");
        return stateCode;
    }else if(strcasecmp("Virgin Islands, U.S.",state) == 0){
        stateCode = ("VI");
        return stateCode;
    }else if(strcasecmp("Vermont",state) == 0){
        stateCode = ("VT");
        return stateCode;
    }else if(strcasecmp("Washington",state) == 0){
        stateCode = ("WA");
        return stateCode;
    }else if(strcasecmp("Wisconsin",state) == 0){
        stateCode = ("WI");
        return stateCode;
    }else if(strcasecmp("West Virginia",state) == 0){
        stateCode = ("WV");
        return stateCode;
    }else if(strcasecmp("Wyoming",state) == 0){
        stateCode = ("WY");
        return stateCode;
    }else{
        stateCode = ("");
        return stateCode;
    }
    
}

char *codeToState(char *code){
    char *state = NULL;
    
    if(strcasecmp("AK",code) == 0){
        state = ("Alaska");
        return state;
    }else if(strcasecmp("AL",code) == 0){
        state = ("Alabama");
        return state;
    }else if(strcasecmp("AR",code) == 0){
        state = ("Arkansas");
        return state;
    }else if(strcasecmp("AS",code) == 0){
        state = ("American Samoa");
        return state;
    }else if(strcasecmp("AZ",code) == 0){
        state = ("Arizona");
        return state;
    }else if(strcasecmp("CA",code) == 0){
        state = ("California");
        return state;
    }else if(strcasecmp("CO",code) == 0){
        state = ("Colorado");
        return state;
    }else if(strcasecmp("CT",code) == 0){
        state = ("Connecticut");
        return state;
    }else if(strcasecmp("DC",code) == 0){
        state = ("District of Columbia");
        return state;
    }else if(strcasecmp("DE",code) == 0){
        state = ("Delaware");
        return state;
    }else if(strcasecmp("FL",code) == 0){
        state = ("Florida");
        return state;
    }else if(strcasecmp("GA",code) == 0){
        state = ("Georgia");
        return state;
    }else if(strcasecmp("GU",code) == 0){
        state = ("Guam");
        return state;
    }else if(strcasecmp("HI",code) == 0){
        state = ("Hawaii");
        return state;
    }else if(strcasecmp("IA",code) == 0){
        state = ("Iowa");
        return state;
    }else if(strcasecmp("ID",code) == 0){
        state = ("Idaho");
        return state;
    }else if(strcasecmp("IL",code) == 0){
        state = ("Illinois");
        return state;
    }else if(strcasecmp("IN",code) == 0){
        state = ("Indiana");
        return state;
    }else if(strcasecmp("KS",code) == 0){
        state = ("Kansas");
        return state;
    }else if(strcasecmp("KY",code) == 0){
        state = ("Kentucky");
        return state;
    }else if(strcasecmp("LA",code) == 0){
        state = ("Louisiana");
        return state;
    }else if(strcasecmp("MA",code) == 0){
        state = ("Massachusetts");
        return state;
    }else if(strcasecmp("MD",code) == 0){
        state = ("Maryland");
        return state;
    }else if(strcasecmp("ME",code) == 0){
        state = ("Maine");
        return state;
    }else if(strcasecmp("MI",code) == 0){
        state = ("Michigan");
        return state;
    }else if(strcasecmp("MN",code) == 0){
        state = ("Minnesota");
        return state;
    }else if(strcasecmp("MO",code) == 0){
        state = ("Missouri");
        return state;
    }else if(strcasecmp("MP",code) == 0){
        state = ("Northern Mariana Islands");
        return state;
    }else if(strcasecmp("MS",code) == 0){
        state = ("Mississippi");
        return state;
    }else if(strcasecmp("MT",code) == 0){
        state = ("Montana");
        return state;
    }else if(strcasecmp("NC",code) == 0){
        state = ("North Carolina");
        return state;
    }else if(strcasecmp("ND",code) == 0){
        state = ("North Dakota");
        return state;
    }else if(strcasecmp("NE",code) == 0){
        state = ("Nebraska");
        return state;
    }else if(strcasecmp("NH",code) == 0){
        state = ("New Hampshire");
        return state;
    }else if(strcasecmp("NJ",code) == 0){
        state = ("New Jersey");
        return state;
    }else if(strcasecmp("NM",code) == 0){
        state = ("New Mexico");
        return state;
    }else if(strcasecmp("NV",code) == 0){
        state = ("Nevada");
        return state;
    }else if(strcasecmp("NY",code) == 0){
        state = ("New York");
        return state;
    }else if(strcasecmp("OH",code) == 0){
        state = ("Ohio");
        return state;
    }else if(strcasecmp("OK",code) == 0){
        state = ("Oklahoma");
        return state;
    }else if(strcasecmp("OR",code) == 0){
        state = ("Oregon");
        return state;
    }else if(strcasecmp("PA",code) == 0){
        state = ("Pennsylvania");
        return state;
    }else if(strcasecmp("PR",code) == 0){
        state = ("Puerto Rico");
        return state;
    }else if(strcasecmp("RI",code) == 0){
        state = ("Rhode Island");
        return state;
    }else if(strcasecmp("SC",code) == 0){
        state = ("South Carolina");
        return state;
    }else if(strcasecmp("SD",code) == 0){
        state = ("South Dakota");
        return state;
    }else if(strcasecmp("TN",code) == 0){
        state = ("Tennessee");
        return state;
    }else if(strcasecmp("TX",code) == 0){
        state = ("Texas");
        return state;
    }else if(strcasecmp("UM",code) == 0){
        state = ("United States Minor Outlying Islands");
        return state;
    }else if(strcasecmp("UT",code) == 0){
        state = ("Utah");
        return state;
    }else if(strcasecmp("VA",code) == 0){
        state = ("Virginia");
        return state;
    }else if(strcasecmp("VI",code) == 0){
        state = ("Virgin Islands, U.S.");
        return state;
    }else if(strcasecmp("VT",code) == 0){
        state = ("Vermont");
        return state;
    }else if(strcasecmp("WA",code) == 0){
        state = ("Washington");
        return state;
    }else if(strcasecmp("WI",code) == 0){
        state = ("Wisconsin");
        return state;
    }else if(strcasecmp("WV",code) == 0){
        state = ("West Virginia");
        return state;
    }else if(strcasecmp("WY",code) == 0){
        state = ("Wyoming");
        return state;
    }else{
        state = ("");
        return state;
    }
}