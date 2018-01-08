MODULE := backends/platform/sdl/deps

MODULE_OBJS := \
	libFLAC/bitreader.o \
	libFLAC/cpu.o \
	libFLAC/crc.o \
	libFLAC/fixed.o \
	libFLAC/format.o \
	libFLAC/lpc.o \
	libFLAC/md5.o \
	libFLAC/memory.o \
	libFLAC/metadata_object.o \
	libFLAC/stream_decoder.o

MODULE_OBJS += \
	libogg/src/bitwise.o \
	libogg/src/framing.o \
	libvorbis/lib/analysis.o \
	libvorbis/lib/bitrate.o \
	libvorbis/lib/block.o \
	libvorbis/lib/codebook.o \
	libvorbis/lib/envelope.o \
	libvorbis/lib/floor0.o \
	libvorbis/lib/floor1.o \
	libvorbis/lib/info.o \
	libvorbis/lib/lookup.o \
	libvorbis/lib/lpc.o \
	libvorbis/lib/lsp.o \
	libvorbis/lib/mapping0.o \
	libvorbis/lib/mdct.o \
	libvorbis/lib/psy.o \
	libvorbis/lib/registry.o \
	libvorbis/lib/res0.o \
	libvorbis/lib/sharedbook.o \
	libvorbis/lib/smallft.o \
	libvorbis/lib/synthesis.o \
	libvorbis/lib/vorbisenc.o \
	libvorbis/lib/vorbisfile.o \
	libvorbis/lib/window.o

ifeq ($(LIBRETRO_USE_TREMOR),yes)
MODULE_OBJS += \
	tremor/bitwise.o \
	tremor/block.o \
	tremor/codebook.o \
	tremor/floor0.o \
	tremor/floor1.o \
	tremor/framing.o \
	tremor/info.o \
	tremor/mapping0.o \
	tremor/mdct.o \
	tremor/registry.o \
	tremor/res012.o \
	tremor/sharedbook.o \
	tremor/synthesis.o \
	tremor/vorbisfile.o \
	tremor/window.o
endif

MODULE_OBJS += \
 	libz/deflate.o \
	libz/gzlib.o \
	libz/uncompr.o \
	libz/zutil.o \
	libz/inffast.o \
	libz/gzread.o \
	libz/crc32.o \
	libz/gzwrite.o \
	libz/inflate.o \
	libz/infback.o \
	libz/inftrees.o \
	libz/trees.o \
	libz/gzclose.o \
	libz/compress.o \
	libz/adler32.o

MODULE_OBJS += \
	libmad/bit.o \
	libmad/decoder.o \
	libmad/frame.o \
	libmad/huffman.o \
	libmad/layer12.o \
	libmad/layer3.o \
	libmad/stream.o \
	libmad/synth.o \
	libmad/timer.o

MODULE_OBJS += \
	libfaad/libfaad/bits.o \
	libfaad/libfaad/cfft.o \
	libfaad/libfaad/common.o \
	libfaad/libfaad/decoder.o \
	libfaad/libfaad/drc.o \
	libfaad/libfaad/error.o \
	libfaad/libfaad/filtbank.o \
	libfaad/libfaad/hcr.o \
	libfaad/libfaad/huffman.o \
	libfaad/libfaad/ic_predict.o \
	libfaad/libfaad/is.o \
	libfaad/libfaad/lt_predict.o \
	libfaad/libfaad/mdct.o \
	libfaad/libfaad/mp4.o \
	libfaad/libfaad/ms.o \
	libfaad/libfaad/output.o \
	libfaad/libfaad/pns.o \
	libfaad/libfaad/pulse.o \
	libfaad/libfaad/ps_dec.o \
	libfaad/libfaad/ps_syntax.o \
	libfaad/libfaad/rvlc.o \
	libfaad/libfaad/sbr_dct.o \
	libfaad/libfaad/sbr_dec.o \
	libfaad/libfaad/sbr_e_nf.o \
	libfaad/libfaad/sbr_fbt.o \
	libfaad/libfaad/sbr_hfadj.o \
	libfaad/libfaad/sbr_hfgen.o \
	libfaad/libfaad/sbr_huff.o \
	libfaad/libfaad/sbr_qmf.o \
	libfaad/libfaad/sbr_syntax.o \
	libfaad/libfaad/sbr_tf_grid.o \
	libfaad/libfaad/specrec.o \
	libfaad/libfaad/syntax.o \
	libfaad/libfaad/tns.o

MODULE_OBJS += \
	libpng/png.o \
	libpng/pngerror.o \
	libpng/pngget.o \
	libpng/pngmem.o \
	libpng/pngpread.o \
	libpng/pngread.o \
	libpng/pngrio.o \
	libpng/pngrtran.o \
	libpng/pngrutil.o \
	libpng/pngset.o \
	libpng/pngtrans.o \
	libpng/pngwrite.o \
	libpng/pngwutil.o \
	libpng/pngwtran.o \
	libpng/pngwio.o

MODULE_OBJS += \
	libjpeg/jaricom.o \
	libjpeg/jcapimin.o \
	libjpeg/jcapistd.o \
	libjpeg/jcarith.o \
	libjpeg/jccoefct.o \
	libjpeg/jccolor.o \
	libjpeg/jcdctmgr.o \
	libjpeg/jcinit.o \
	libjpeg/jchuff.o \
	libjpeg/jcmarker.o \
	libjpeg/jcmainct.o \
	libjpeg/jcmaster.o \
	libjpeg/jcomapi.o \
	libjpeg/jcphuff.o \
	libjpeg/jcprepct.o \
	libjpeg/jcsample.o \
	libjpeg/jdapimin.o \
	libjpeg/jdapistd.o \
	libjpeg/jdarith.o \
	libjpeg/jdcoefct.o \
	libjpeg/jdcolor.o \
	libjpeg/jddctmgr.o \
	libjpeg/jdhuff.o \
	libjpeg/jdinput.o \
	libjpeg/jdmarker.o \
	libjpeg/jdmainct.o \
	libjpeg/jdmaster.o \
	libjpeg/jdmerge.o \
	libjpeg/jdphuff.o \
	libjpeg/jdpostct.o \
	libjpeg/jdsample.o \
	libjpeg/jdtrans.o \
	libjpeg/jerror.o \
	libjpeg/jidctflt.o \
	libjpeg/jidctfst.o \
	libjpeg/jidctint.o \
	libjpeg/jidctred.o \
	libjpeg/jfdctflt.o \
	libjpeg/jfdctfst.o \
	libjpeg/jfdctint.o \
	libjpeg/jmemmgr.o \
	libjpeg/jmemnobs.o \
	libjpeg/jquant1.o \
	libjpeg/jquant2.o \
	libjpeg/jutils.o \
	libjpeg/jsimd_none.o

MODULE_OBJS += \
	theora/lib/bitpack.o \
	theora/lib/decinfo.o \
	theora/lib/decode.o \
	theora/lib/dequant.o \
	theora/lib/fragment.o \
	theora/lib/huffdec.o \
	theora/lib/idct.o \
	theora/lib/info.o \
	theora/lib/internal.o \
	theora/lib/quant.o \
	theora/lib/state.o

MODULE_OBJS += \
	freetype/src/autofit/afangles.o \
	freetype/src/autofit/afblue.o \
	freetype/src/autofit/afcjk.o \
	freetype/src/autofit/afdummy.o \
	freetype/src/autofit/afglobal.o \
	freetype/src/autofit/afhints.o \
	freetype/src/autofit/afindic.o \
	freetype/src/autofit/aflatin.o \
	freetype/src/autofit/afloader.o \
	freetype/src/autofit/afmodule.o \
	freetype/src/autofit/afpic.o \
	freetype/src/autofit/afranges.o \
	freetype/src/autofit/afshaper.o \
	freetype/src/autofit/afwarp.o \
	freetype/src/base/basepic.o \
	freetype/src/base/ftadvanc.o \
	freetype/src/base/ftapi.o \
	freetype/src/base/ftbitmap.o \
	freetype/src/base/ftcalc.o \
	freetype/src/base/ftgloadr.o \
	freetype/src/base/ftglyph.o \
	freetype/src/base/fthash.o \
	freetype/src/base/ftinit.o \
	freetype/src/base/ftobjs.o \
	freetype/src/base/ftsystem.o \
	freetype/src/base/ftoutln.o \
	freetype/src/base/ftrfork.o \
	freetype/src/base/ftstream.o \
	freetype/src/base/ftstroke.o \
	freetype/src/base/fttrigon.o \
	freetype/src/base/ftutil.o \
	freetype/src/bdf/bdfdrivr.o \
	freetype/src/bdf/bdflib.o \
	freetype/src/cid/cidriver.o \
	freetype/src/cid/cidgload.o \
	freetype/src/cid/cidload.o \
	freetype/src/cid/cidobjs.o \
	freetype/src/cid/cidparse.o \
	freetype/src/cff/cf2arrst.o \
	freetype/src/cff/cf2blues.o \
	freetype/src/cff/cf2error.o \
	freetype/src/cff/cf2ft.o \
	freetype/src/cff/cf2font.o \
	freetype/src/cff/cf2hints.o \
	freetype/src/cff/cf2intrp.o \
	freetype/src/cff/cf2read.o \
	freetype/src/cff/cf2stack.o \
	freetype/src/cff/cffcmap.o \
	freetype/src/cff/cffgload.o \
	freetype/src/cff/cffload.o \
	freetype/src/cff/cffobjs.o \
	freetype/src/cff/cffparse.o \
	freetype/src/cff/cffpic.o \
	freetype/src/cff/cffdrivr.o \
	freetype/src/gzip/ftgzip.o \
	freetype/src/lzw/ftlzw.o \
	freetype/src/pcf/pcfdrivr.o \
	freetype/src/pcf/pcfread.o \
	freetype/src/pcf/pcfutil.o \
	freetype/src/pfr/pfrcmap.o \
	freetype/src/pfr/pfrdrivr.o \
	freetype/src/pfr/pfrgload.o \
	freetype/src/pfr/pfrload.o \
	freetype/src/pfr/pfrobjs.o \
	freetype/src/pfr/pfrsbit.o \
	freetype/src/psaux/afmparse.o \
	freetype/src/psaux/psconv.o \
	freetype/src/psaux/psobjs.o \
	freetype/src/psaux/t1cmap.o \
	freetype/src/psaux/t1decode.o \
	freetype/src/psaux/psauxmod.o \
	freetype/src/pshinter/pshalgo.o \
	freetype/src/pshinter/pshglob.o \
	freetype/src/pshinter/pshmod.o \
	freetype/src/pshinter/pshpic.o \
	freetype/src/pshinter/pshrec.o \
	freetype/src/psnames/psmodule.o \
	freetype/src/raster/ftrend1.o \
	freetype/src/raster/ftraster.o \
	freetype/src/raster/rastpic.o \
	freetype/src/sfnt/sfdriver.o \
	freetype/src/sfnt/sfntpic.o \
	freetype/src/sfnt/sfobjs.o \
	freetype/src/sfnt/ttbdf.o \
	freetype/src/sfnt/ttcmap.o \
	freetype/src/sfnt/ttkern.o \
	freetype/src/sfnt/ttload.o \
	freetype/src/sfnt/ttmtx.o \
	freetype/src/sfnt/ttpost.o \
	freetype/src/sfnt/ttsbit.o \
	freetype/src/smooth/ftgrays.o \
	freetype/src/smooth/ftsmooth.o \
	freetype/src/type1/t1afm.o \
	freetype/src/type1/t1driver.o \
	freetype/src/type1/t1gload.o \
	freetype/src/type1/t1load.o \
	freetype/src/type1/t1objs.o \
	freetype/src/type1/t1parse.o \
	freetype/src/type42/t42drivr.o \
	freetype/src/type42/t42objs.o \
	freetype/src/type42/t42parse.o \
	freetype/src/truetype/ttdriver.o \
	freetype/src/truetype/ttgload.o \
	freetype/src/truetype/ttgxvar.o \
	freetype/src/truetype/ttinterp.o \
	freetype/src/truetype/ttobjs.o \
	freetype/src/truetype/ttpload.o \
	freetype/src/winfonts/winfnt.o

MODULE_OBJS += \
	libretro-common/file/retro_dirent.o \
	libretro-common/file/retro_stat.o \
  	libretro-common/file/file_path.o \
	libretro-common/compat/compat_strl.o

MODULE_OBJS += \
	sdl-libretro/src/SDL_error.o sdl-libretro/src/SDL_fatal.o \
	sdl-libretro/src/SDL.o sdl-libretro/src/audio/SDL_wave.o \
	sdl-libretro/src/audio/SDL_audiodev.o sdl-libretro/src/audio/SDL_mixer_MMX.o \
	sdl-libretro/src/audio/SDL_mixer_m68k.o sdl-libretro/src/audio/SDL_audiocvt.o \
	sdl-libretro/src/audio/SDL_audio.o sdl-libretro/src/audio/SDL_mixer.o \
	sdl-libretro/src/audio/SDL_mixer_MMX_VC.o sdl-libretro/src/cdrom/SDL_cdrom.o \
	sdl-libretro/src/cpuinfo/SDL_cpuinfo.o sdl-libretro/src/events/SDL_active.o \
	sdl-libretro/src/events/SDL_quit.o sdl-libretro/src/events/SDL_mouse.o \
	sdl-libretro/src/events/SDL_events.o sdl-libretro/src/events/SDL_keyboard.o \
	sdl-libretro/src/events/SDL_expose.o sdl-libretro/src/events/SDL_resize.o \
	sdl-libretro/src/file/SDL_rwops.o sdl-libretro/src/stdlib/SDL_string.o \
	sdl-libretro/src/stdlib/SDL_malloc.o sdl-libretro/src/stdlib/SDL_iconv.o \
	sdl-libretro/src/stdlib/SDL_getenv.o sdl-libretro/src/stdlib/SDL_qsort.o \
	sdl-libretro/src/stdlib/SDL_stdlib.o sdl-libretro/src/thread/SDL_thread.o \
	sdl-libretro/src/timer/SDL_timer.o sdl-libretro/src/video/SDL_cursor.o \
	sdl-libretro/src/video/SDL_blit_0.o sdl-libretro/src/video/SDL_yuv.o \
	sdl-libretro/src/video/SDL_bmp.o sdl-libretro/src/video/SDL_video.o \
	sdl-libretro/src/video/SDL_yuv_mmx.o sdl-libretro/src/video/SDL_surface.o \
	sdl-libretro/src/video/SDL_pixels.o sdl-libretro/src/video/SDL_stretch.o \
	sdl-libretro/src/video/SDL_blit_A.o sdl-libretro/src/video/SDL_blit_N.o \
	sdl-libretro/src/video/SDL_blit_1.o sdl-libretro/src/video/SDL_blit.o \
	sdl-libretro/src/video/SDL_yuv_sw.o sdl-libretro/src/video/SDL_RLEaccel.o \
	sdl-libretro/src/video/SDL_gamma.o sdl-libretro/src/joystick/SDL_joystick.o \
	sdl-libretro/src/video/libretro/SDL_LIBRETROmouse.o \
	sdl-libretro/src/video/libretro/SDL_LIBRETROevents.o \
	sdl-libretro/src/video/libretro/SDL_LIBRETROvideo.o \
	sdl-libretro/src/video/libretro/SDL_LIBRETROkeyboard.o sdl-libretro/src/thread/pthread/SDL_syscond.o \
	sdl-libretro/src/thread/pthread/SDL_syssem.o sdl-libretro/src/thread/pthread/SDL_sysmutex.o \
	sdl-libretro/src/thread/pthread/SDL_systhread.o sdl-libretro/src/joystick/libretro/SDL_sysjoystick.o \
	sdl-libretro/src/timer/libretro/SDL_systimer.o sdl-libretro/src/audio/libretro/SDL_LIBRETROaudio.o \
	sdl-libretro/src/loadso/dummy/SDL_sysloadso.o 

ifeq ($(platform), unix)
MODULE_OBJS += sdl-libretro/src/cdrom/linux/SDL_syscdrom.o
endif
ifeq ($(platform), win)
MODULE_OBJS += sdl-libretro/src/cdrom/win32/SDL_syscdrom.o
endif
ifeq ($(platform), wiiu)
MODULE_OBJS += sdl-libretro/src/cdrom/dummy/SDL_syscdrom.o
endif

# We don't use rules.mk but rather manually update OBJS and MODULE_DIRS.
#MODULE_OBJS := $(addprefix $(MODULE)/, $(MODULE_OBJS))
#OBJS := $(MODULE_OBJS) $(OBJS)
#MODULE_DIRS += $(sort $(dir $(MODULE_OBJS)))
# Include common rules
include $(srcdir)/rules.mk
