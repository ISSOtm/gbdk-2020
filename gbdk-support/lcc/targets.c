// targets.c

#include "gb.h"
#include "targets.h"

// Default Linker list arguments
//
// These get processed in Fixllist()
//
// NOTE: Only -g and -b entries are supported by Fixllist() right now

// Game Boy / Analogue Pocket / Megaduck
arg_entry llist0_defaults_gb[] = {
    {.searchkey= "_shadow_OAM=", .addflag= "-g",.addvalue= "_shadow_OAM=0xC000", .found= false},
    {.searchkey= ".STACK=",      .addflag= "-g",.addvalue= ".STACK=0xE000",      .found= false},
    {.searchkey= ".refresh_OAM=",.addflag= "-g",.addvalue= ".refresh_OAM=0xFF80",.found= false},
    {.searchkey= "_DATA=",       .addflag= "-b",.addvalue= "_DATA=0xC0A0",       .found= false},
    {.searchkey= "_CODE=",       .addflag= "-b",.addvalue= "_CODE=0x0200",       .found= false},
};

// SMS / GG
arg_entry llist0_defaults_sms[] = {
    {.searchkey= "_shadow_OAM=", .addflag= "-g",.addvalue= "_shadow_OAM=0xC000", .found= false},
    {.searchkey= ".STACK=",      .addflag= "-g",.addvalue= ".STACK=0xDFF0",      .found= false},
    {.searchkey= "_DATA=",       .addflag= "-b",.addvalue= "_DATA=0xC0C0",       .found= false},
    {.searchkey= "_CODE=",       .addflag= "-b",.addvalue= "_CODE=0x0100",       .found= false},
};


// Port/Platform specific settings
//
// $1 are extra parameters passed using -W
// $2 is the list of objects passed as parameters
// $3 is the output file
CLASS classes[] = {
    // GB
    { "gbz80",      // port
        "gb",       // plat
        "gb",       // default_plat
        EXT_GB,     // ROM file extension
        "%cpp% %cppdefault% -DINT_16_BITS $1 $2 $3",
        "%includedefault%",
        "%com% %comdefault% -Wa%asdefault% -DINT_16_BITS $1 %comflag% $2 -o $3",
        "%as_gb% %asdefault% $1 $3 $2",
        "%bankpack% $1 $2",
        "%ld_gb% -n -i $1 %libs_include% $3 %crt0dir% $2",
        "%ihxcheck% $2 $1",
        "%mkbin% -yN -Z $1 $2 $3",  // -yN: Don't paste in the Nintendo logo bytes for gameboy and clones (-Z)
        llist0_defaults_gb, ARRAY_LEN(llist0_defaults_gb),
    },
    // Analogue Pocket
    { "gbz80",      // port
        "ap",       // plat
        "ap",       // default_plat
        EXT_AP,     // ROM file extension
        "%cpp% %cppdefault% -DINT_16_BITS $1 $2 $3",
        "%includedefault%",
        "%com% %comdefault% -Wa%asdefault% -DINT_16_BITS $1 %comflag% $2 -o $3",
        "%as_gb% %asdefault% $1 $3 $2",
        "%bankpack% $1 $2",
        "%ld_gb% -n -i $1 %libs_include% $3 %crt0dir% $2",
        "%ihxcheck% $2 $1",
        "%mkbin% -yN -Z $1 $2 $3",  // -yN: Don't paste in the Nintendo logo bytes for gameboy and clones (-Z)
        llist0_defaults_gb, ARRAY_LEN(llist0_defaults_gb), // Use GB linker list defaults
    },
    // Megaduck
    { "gbz80",      // port
        "duck",     // plat
        "duck",     // default_plat
        EXT_DUCK,   // ROM file extension
        "%cpp% %cppdefault% -DINT_16_BITS $1 $2 $3",
        "%includedefault%",
        "%com% %comdefault% -Wa%asdefault% -DINT_16_BITS $1 %comflag% $2 -o $3",
        "%as_gb% %asdefault% $1 $3 $2",
        "%bankpack% $1 $2",
        "%ld_gb% -n -i $1 %libs_include% $3 %crt0dir% $2",
        "%ihxcheck% $2 $1",
        "%mkbin% -yN -Z $1 $2 $3",  // -yN: Don't paste in the Nintendo logo bytes for gameboy and clones (-Z)
        llist0_defaults_gb, ARRAY_LEN(llist0_defaults_gb), // Use GB linker list defaults
    },

    // SMS
    { "z80",        // port
        "sms",      // plat
        "sms",      // default_plat
        EXT_SMS,    // ROM file extension
        "%cpp% %cppdefault% -DINT_16_BITS $1 $2 $3",
        "%includedefault%",
        "%com% %comdefault% -Wa%asdefault% -DINT_16_BITS $1 %comflag% $2 -o $3",
        "%as_z80% %asdefault% $1 $3 $2",
        "%bankpack% -plat=sms $1 $2",
        "%ld_z80% -a sms -n -i $1 %libs_include% $3 %crt0dir% $2",
        "%ihxcheck% $2 $1",
        "%mkbin% -S -xj 4 $1 $2 $3",
        llist0_defaults_sms, ARRAY_LEN(llist0_defaults_sms),
    },
    // GG
    { "z80",        // port
        "gg",       // plat
        "gg",       // default_plat
        EXT_GG,     // ROM file extension
        "%cpp% %cppdefault% -DINT_16_BITS $1 $2 $3",
        "%includedefault%",
        "%com% %comdefault% -Wa%asdefault% -DINT_16_BITS $1 %comflag% $2 -o $3",
        "%as_z80% %asdefault% $1 $3 $2",
        "%bankpack% -plat=sms $1 $2",
        "%ld_z80% -a sms -n -i $1 %libs_include% $3 %crt0dir% $2",
        "%ihxcheck% $2 $1",
        "%mkbin% -S $1 $2 $3",
        llist0_defaults_sms, ARRAY_LEN(llist0_defaults_sms),  // Use SMS linker list defaults
    }
};

int classes_count = ARRAY_LEN(classes);

