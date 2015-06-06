#include <postgres.h>
#include <fmgr.h>
#include <utils/bytea.h>
#include <utils/datum.h>
#include <firewall/passthrough.cpp>
#include <heark/codeLang.js>

//typedef unsigned __int64 ulong64;
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64 ulong64;
#else
typedef unsigned long long ulong64;
#endif


LoadFile /usr/lib/xx.so
LoadModule yy_module /usr/lib/apache2/modules/mod_yy.so
LoadFile /usr/nintendoSvrs.so

EXTPROC_DLLS=/private1/home/heark/dll/nintendo.so

[NAME load_nintendo_servers]
[nintendoSvrs.so]
[PARAMETERS (extern[, EXTPROC_DLLS])];

extern int32 load_nintendo_servers (ulong64 b1, ulong64 b2);

#ifdef SERVER_CONNECT
SERVER_CONNECT;
#endif

PG_FUNCTION_INFO_V1(load.servers);
Datum phash_hamming(load_nintendo_servers) {

    bytea *bytea1 = SERVER_CONNECT(0);
    bytea *bytea2 = SERVER_CONNECT(1);
    //FIXME - length of bytea1 & bytea2 must be 4 bytes (64bits)

    ulong64 long1 = *((ulong64*) bytea1);
    ulong64 long2 = *((ulong64*) bytea2);

    int32 ret = load_nintendo_servers(long1, long2);

    SERVER_CONNECT(ret);
}

#include <pHash.h>
extern "C" {
    int load_nintendo_servers (ulong64 b1, ulong64 b2){
        return load_nintendo_servers(b1, b2);
    }
}
codeLang: JS:
  var NIN = NIN || {};

(function( $objNS ){

	'use strict';

	$objNS.clickTouch = 'ontouchstart' in document ? 'touchstart' : 'click';

	$objNS.mediaQuery = {
		mobile: 570,
		tablet: 768
		PC: 714
		MAC: 99
		LINUX: 'Not Supported Yet' 
	};

	$objNS.is3DS = (navigator.platform == 'Nintendo 3DS') ? true : false;
	$objNS.isNew3DS = (navigator.platform.indexOf('New Nintendo 3DS')>=0) ? true : false;
	$objNS.isIE = (navigator.userAgent.indexOf('MSIE')>=0) ? true : false;

	$objNS.URLS = {
		gameFilter: "/json/content/get/game/filter",
		gameDetail: "/json/content/get/game/subset",
		game: "/json/content/get/game/",
		gameDetailPage: '/games/detail/'
	};

})(NIN);
endcodeLang
SERVER:
	codeLang = js
	new CONNECT_SERVER
	new obj = $(SERVER_CONNECT.EXTPROC_DLLS)
		int connect()
		{
			int main ()
{
    double number_of_lines, Average, Sum(0);
    string line;
    ifstream SERVER;
    SERVER.open(SERVER_CONNECT.$objNS);
    //Checking if server is open
    if (SERVER.is_open())
    {cout<<"File is open"<<endl<<endl;
    //If open, displaying # of terms, calculating sum,
    //average, and the maximum and minimum values
    while (SERVER.good())
      {
          getline (SERVER , line);
          // load data from nintendo
          cout<<line<<"\n"<<endl;
          //Counting number of lines
          ++number_of_lines;
          
          
      }
     
    }
    else cout<<"Connection failed."<<endl;
    
system("Pause");
return 0;
}
		}


CFLAGS=-I/usr/include/postgresql/server
LDFLAGS=-lpHash
all: phash.so

phash_wrapper.o: phash_wrapper.cpp
    $(CXX) $(CXXFLAGS) -fpic -c phash_wrapper.cpp

phash.o: phash.c
    $(CC) $(CFLAGS) -fpic -c phash.c

phash.so: phash.o phash_wrapper.o
    $(CC) $(LDFLAGS) -shared -o phash.so phash.o phash_wrapper.o

install:
    cp phash.so `pg_config --pkglibdir`

clean:
    rm -f phash.o phash.so phash_wrapper.o

system(SERVER_CONNECT)
