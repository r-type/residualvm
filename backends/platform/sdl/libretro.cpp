
#include <string.h>
#include <stdio.h>

#include "libretro.h"

#define INCLUDED_FROM_BASE_VERSION_CPP
#include "base/internal_version.h"

#ifdef HAVE_LIBCO
#define LIBCO_C 
#include "libco.h"
#include "deps/libretro-common/libco/libco.c"
cothread_t mainThread;
cothread_t emuThread;
#endif

#define LOGI printf

char RPATH[512];
char RETRO_DIR[512];
const char *retro_save_directory;
const char *retro_system_directory;
const char *retro_content_directory;
char retro_system_data[512];

bool opt_analog;

int retrow=640;
int retroh=480;
int max_width   = 640;
int max_height  = 480;
int NEWGAME_SIZE=0;

#ifndef HAVE_LIBCO
extern void RetroLoop();
int CPULOOP=1;
#endif
int pauseg=0;

unsigned /*short*/ int *videoBuffer;

static retro_video_refresh_t video_cb;
static retro_environment_t environ_cb;
static retro_audio_sample_batch_t audio_batch_cb;
retro_audio_sample_t audio_cb;
retro_input_poll_t input_poll_cb;
retro_input_state_t input_state_cb;

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb  =cb; }
void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

int sdlinitok=0;

void retro_audiocb(signed short int *sound_buffer,int sndbufsize){
   int x; 

   if(pauseg==0)
 	audio_batch_cb(sound_buffer, sndbufsize);
}

int pre_main(const char *argv);
int smain(int argc, char *argv[]);

#include <time.h>
#include <sys/time.h>

#if defined(_WIN32)
#include <time.h>
#include <sys/time.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif
void libretro_audio_cb(int16_t left, int16_t right){
	if(sdlinitok==0)return;
	audio_cb(left,right);	
	printf("not used here!\n");
}

short int libretro_input_state_cb(unsigned port,unsigned device,unsigned index,unsigned id){
	if(sdlinitok==0)return 0;
	return input_state_cb(port,device,index,id);
} 

#ifdef __cplusplus
}
#endif
#ifdef HAVE_LIBCO
long frame=0;
unsigned long  Ktime=0 , LastFPSTime=0;
//NO SURE FIND BETTER WAY TO COME BACK IN MAIN THREAD IN HATARI GUI
#ifdef WIIU
#include <features_cpu.h>
#endif

long GetTicks(void)
{ // in MSec
#ifndef _ANDROID_

#ifdef __CELLOS_LV2__

   //#warning "GetTick PS3\n"

   unsigned long	ticks_micro;
   uint64_t secs;
   uint64_t nsecs;

   sys_time_get_current_time(&secs, &nsecs);
   ticks_micro =  secs * 1000000UL + (nsecs / 1000);

   return ticks_micro/1000;
#elif WIIU

   return (cpu_features_get_time_usec())/1000;

#else
   struct timeval tv;
   gettimeofday (&tv, NULL);
   return (tv.tv_sec*1000000 + tv.tv_usec)/1000;
#endif

#else

   struct timespec now;
   clock_gettime(CLOCK_MONOTONIC, &now);
   return (now.tv_sec*1000000 + now.tv_nsec/1000)/1000;
#endif

} 
int gui_poll_events(void)
{
   Ktime = GetTicks();

   if(Ktime - LastFPSTime >= 1000/60)
   { 
//	  slowdown=0;
      LastFPSTime = Ktime;		
      co_switch(mainThread);
      return 1;
   }

   return 0;
}

void retro_leave_thread(void)
{
   co_switch(mainThread);
}

static void retro_wrap_emulator()
{    
   LOGI("WRAP EMU THD\n");
   pre_main(RPATH);


   LOGI("EXIT EMU THD\n");
   pauseg=-1;
   sdlinitok=0;

   //environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0); 

   // Were done here
   co_switch(mainThread);

   // Dead emulator, but libco says not to return
   while(true)
   {
      LOGI("Running a dead emulator.");
      co_switch(mainThread);
   }

}
#endif

//Args for experimental_cmdline
static char ARGUV[64][1024];
static unsigned char ARGUC=0;

// Args for Core
static char XARGV[64][1024];
static const char* xargv_cmd[64];
int PARAMCOUNT=0;
#include <ctype.h>

#include <libgen.h>
#include <string.h>

extern int vmain(int argc, char *argv[]);

void parse_cmdline( const char *argv );

void Add_Option(const char* option)
{
   static int first=0;

   if(first==0)
   {
      PARAMCOUNT=0;	
      first++;
   }

   sprintf(XARGV[PARAMCOUNT++],"%s\0",option);
}

#ifdef WIIU

#include <stdio.h>
#include <string.h>
char *dirname (char *path)
{
       char *p;
       if( path == NULL || *path == '\0' )
               return ".";
       p = path + strlen(path) - 1;
       while( *p == '/' ) {
               if( p == path )
                       return path;
               *p-- = '\0';
       }
       while( p >= path && *p != '/' )
               p--;
       return
               p < path ? "." :
               p == path ? "/" :
               (*p = '\0', path);
}
#endif

int pre_main(const char *argv)
{
   int i;
   bool Only1Arg;

   parse_cmdline(argv); 

   Only1Arg = (strcmp(ARGUV[0],"scummvm") == 0) ? 0 : 1;

   for (i = 0; i<64; i++)
      xargv_cmd[i] = NULL;


   if(Only1Arg)
   {  
      int cfgload=0;

      Add_Option("scummvm");

      Add_Option("--joystick=0");
      Add_Option("--savepath=sd:/retroarch/cores/system");
      Add_Option("--extrapath=sd:/retroarch/cores/system");
      Add_Option("--themepath=sd:/retroarch/cores/system");
      Add_Option("--bpp=32");

      if (strlen(RPATH) >= strlen(".scummvm")){
	if(!strcasecmp(&RPATH[strlen(RPATH)-strlen(".scummvm")], ".scummvm")){
      			char* path = strdup(RPATH);
      			char* gamedir = dirname(path);
			// Retrieve the file data.
         		FILE * gamefile;
         		if (gamefile = fopen(RPATH, "r"))
         		{
				Add_Option("-p");

            			char filedata[400];
            			fgets(filedata , 400, gamefile);
            			fclose(gamefile);

				char buffer[400];
 				sprintf(buffer, "%s\0", gamedir);
				Add_Option(buffer);
 				sprintf(buffer, "%s\0", filedata);
				int lenbuf= strlen(buffer);
				buffer[(lenbuf - 1)] = '\0';
				//printf("(%s)\n",buffer);
				Add_Option(buffer);
		        }
			cfgload=1;
	}
      }

      if(cfgload==0) {
	//	Add_Option("-verbose");
		//	Add_Option("-joydev1");
			//Add_Option("4");
		//	Add_Option("-joydev2");
		//	Add_Option("-c");
      		Add_Option(RPATH);
      }

//      Add_Option(RPATH);
   }
   else
   { // Pass all cmdline args
      for(i = 0; i < ARGUC; i++)
         Add_Option(ARGUV[i]);
   }

   for (i = 0; i < PARAMCOUNT; i++)
   {
      xargv_cmd[i] = (char*)(XARGV[i]);
      LOGI("%2d  %s\n",i,XARGV[i]);
   }

   smain(PARAMCOUNT,( char **)xargv_cmd); 

   xargv_cmd[PARAMCOUNT - 2] = NULL;

   return 0;
}

void parse_cmdline(const char *argv)
{
	char *p,*p2,*start_of_word;
	int c,c2;
	static char buffer[512*4];
	enum states { DULL, IN_WORD, IN_STRING } state = DULL;
	
	strcpy(buffer,argv);
	strcat(buffer," \0");

	for (p = buffer; *p != '\0'; p++)
   {
      c = (unsigned char) *p; /* convert to unsigned char for is* functions */
      switch (state)
      {
         case DULL: /* not in a word, not in a double quoted string */
            if (isspace(c)) /* still not in a word, so ignore this char */
               continue;
            /* not a space -- if it's a double quote we go to IN_STRING, else to IN_WORD */
            if (c == '"')
            {
               state = IN_STRING;
               start_of_word = p + 1; /* word starts at *next* char, not this one */
               continue;
            }
            state = IN_WORD;
            start_of_word = p; /* word starts here */
            continue;
         case IN_STRING:
            /* we're in a double quoted string, so keep going until we hit a close " */
            if (c == '"')
            {
               /* word goes from start_of_word to p-1 */
               //... do something with the word ...
               for (c2 = 0,p2 = start_of_word; p2 < p; p2++, c2++)
                  ARGUV[ARGUC][c2] = (unsigned char) *p2;
               ARGUC++; 

               state = DULL; /* back to "not in word, not in string" state */
            }
            continue; /* either still IN_STRING or we handled the end above */
         case IN_WORD:
            /* we're in a word, so keep going until we get to a space */
            if (isspace(c))
            {
               /* word goes from start_of_word to p-1 */
               //... do something with the word ...
               for (c2 = 0,p2 = start_of_word; p2 <p; p2++,c2++)
                  ARGUV[ARGUC][c2] = (unsigned char) *p2;
               ARGUC++; 

               state = DULL; /* back to "not in word, not in string" state */
            }
            continue; /* either still IN_WORD or we handled the end above */
      }	
   }
}
void texture_init(){
        memset(videoBuffer, 0, sizeof(videoBuffer));
} 

void retro_set_environment(retro_environment_t cb)
{
   environ_cb = cb;
   bool tmp = true;
   environ_cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &tmp);

   struct retro_variable variables[] = {
      {
         "residualvm_sdl_var1","Use var1; OFF|ON",
      },
      { NULL, NULL },
   };

   cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
}

static void update_variables(void)
{
   struct retro_variable var = {0};

 
   var.key = "residualvm_sdl_var1";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      fprintf(stderr, "value: %s\n", var.value);
      if (strcmp(var.value, "OFF") == 0)
         opt_analog = false;
      if (strcmp(var.value, "ON") == 0)
         opt_analog = true;

        fprintf(stderr, "[libretro-test]: var1: %s.\n",opt_analog?"ON":"OFF");
   }

}

void update_input()
{
  input_poll_cb();
}


#if 0
static void keyboard_cb(bool down, unsigned keycode, uint32_t character, uint16_t mod)
{
}
#endif

/************************************
 * libretro implementation
 ************************************/

void retro_get_system_info(struct retro_system_info *info)
{
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
    	memset(info, 0, sizeof(*info));
	info->library_name = "residulvm-libretro-sdl-tinygl";
	info->library_version = SCUMMVM_VERSION GIT_VERSION; 
	info->need_fullpath = true;
	info->valid_extensions = "exe|scum|scummvm";
}

void update_geometry()
{
   struct retro_system_av_info system_av_info;
   system_av_info.geometry.base_width = retrow;
   system_av_info.geometry.base_height = retroh;
   system_av_info.geometry.aspect_ratio = (float)(4.0/3.0);
   environ_cb(RETRO_ENVIRONMENT_SET_GEOMETRY, &system_av_info);
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
   update_variables();

   info->geometry.base_width  = retrow;
   info->geometry.base_height = retroh;

   printf("AV_INFO: width=%d height=%d\n",info->geometry.base_width,info->geometry.base_height);

   info->geometry.max_width  = retrow;
   info->geometry.max_height = retroh;
   max_width=retrow;
   max_height=retroh;

   printf("AV_INFO: max_width=%d max_height=%d\n",info->geometry.max_width,info->geometry.max_height);

   info->geometry.aspect_ratio = (float)(4.0/3.0);

   printf( "AV_INFO: aspect_ratio = %f\n",info->geometry.aspect_ratio);

   info->timing.fps            = 60.0;
   info->timing.sample_rate    = 44100.0;

   printf( "AV_INFO: fps = %f sample_rate = %f\n",info->timing.fps,info->timing.sample_rate);

}

void retro_set_controller_port_device(unsigned port, unsigned device)
{
    (void)port;
    (void)device;
}

size_t retro_serialize_size(void)
{
	return 0;
}

bool retro_serialize(void *data, size_t size)
{
    return false;
}

bool retro_unserialize(const void *data, size_t size)
{
    return false;
}

void retro_cheat_reset(void)
{}

void retro_cheat_set(unsigned index, bool enabled, const char *code)
{
    (void)index;
    (void)enabled;
    (void)code;
}

bool retro_load_game(const struct retro_game_info *info)
{    
	const char *full_path;

	if (info){
	    	full_path = info->path;
	
		strcpy(RPATH,full_path);
	}
	else sprintf(RPATH,"\0");

	printf("LOAD EMU\n");

    	return true;
}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info)
{
    (void)game_type;
    (void)info;
    (void)num_info;
    return false;
}

void retro_unload_game(void)
{
    //pauseg=-1;
}

unsigned retro_get_region(void)
{
    return RETRO_REGION_NTSC;
}

unsigned retro_api_version(void)
{
    return RETRO_API_VERSION;
}

void *retro_get_memory_data(unsigned id)
{
    return NULL;
}

size_t retro_get_memory_size(unsigned id)
{
    return 0;
}

void retro_init(void)
{
   const char *system_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir)
   {
      // if defined, use the system directory			
      retro_system_directory=system_dir;		
   }		   

   const char *content_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY, &content_dir) && content_dir)
   {
      // if defined, use the system directory			
      retro_content_directory=content_dir;		
   }			

   const char *save_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_dir) && save_dir)
   {
      // If save directory is defined use it, otherwise use system directory
      retro_save_directory = *save_dir ? save_dir : retro_system_directory;      
   }
   else
   {
      // make retro_save_directory the same in case RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY is not implemented by the frontend
      retro_save_directory=retro_system_directory;
   }

   if(retro_system_directory==NULL)sprintf(RETRO_DIR, "%s\0",".");
   else sprintf(RETRO_DIR, "%s\0", retro_system_directory);

   sprintf(retro_system_data, "%s/scummvm\0",RETRO_DIR);

   LOGI("Retro SYSTEM_DIRECTORY %s\n",retro_system_directory);
   LOGI("Retro SAVE_DIRECTORY %s\n",retro_save_directory);
   LOGI("Retro CONTENT_DIRECTORY %s\n",retro_content_directory);


    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
    //enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;

    if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
    {
        fprintf(stderr, "Pixel format XRGB8888 not supported by platform, cannot use.\n");
        exit(0);
    }

   struct retro_input_descriptor inputDescriptors[] = {
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Right" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "R2" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "L2" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "R3" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L3, "L3" }
	};
	environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, &inputDescriptors);

/*
    struct retro_keyboard_callback cbk = { keyboard_cb };
    environ_cb(RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK, &cbk);
*/
  	update_variables();
#ifdef HAVE_LIBCO
   if(!emuThread && !mainThread)
   {
      mainThread = co_active();
      emuThread = co_create(65536*sizeof(void*), retro_wrap_emulator);
   }
#endif

}

int retro_quit=0;

void retro_deinit(void)
{ 
#ifdef HAVE_LIBCO

   LOGI("send exit emu\n");
   while(pauseg!=-1)
   {
      retro_quit=1;
      co_switch(emuThread);
   }

   LOGI("exit emu\n");

   co_switch(mainThread);
   LOGI("exit main\n");

   if(emuThread)
   {	 
      co_delete(emuThread);
      emuThread = 0;
   }
#else
        LOGI("send exit emu\n");
	//Quit_Hatari();
#endif
        printf("Retro DeInit\n");
}

void retro_reset(void)
{
}

void retro_run(void)
{
	bool updated = false;

	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      		update_variables(); 

   if (NEWGAME_SIZE == 1)
   {
      struct retro_system_av_info ninfo;

      retro_get_system_av_info(&ninfo);

      environ_cb(RETRO_ENVIRONMENT_SET_SYSTEM_AV_INFO, &ninfo);

      printf("ChangeAV: w:%d h:%d ra:%f.\n",
               ninfo.geometry.base_width, ninfo.geometry.base_height, (float)retrow/(float)retroh);

      NEWGAME_SIZE=0;
   }
   else if (NEWGAME_SIZE == 2){
      update_geometry();
      printf("Update Geometry w:%d h:%d a:%f\n",retrow,retroh,(float)retrow/(float)retroh);
      NEWGAME_SIZE=0;
   }

#ifndef HAVE_LIBCO
        static bool firstcall=true;
	if(firstcall){
		firstcall=false;

		pre_main(RPATH);
		sdlinitok=1;
	}

	RetroLoop();
#else
        static bool firstcall=true;
	if(firstcall){
		firstcall=false;
		sdlinitok=1;
	}

#endif
	update_input();

        video_cb(videoBuffer, retrow, retroh, retrow <<2);
#ifdef HAVE_LIBCO
   co_switch(emuThread);
#endif
}

