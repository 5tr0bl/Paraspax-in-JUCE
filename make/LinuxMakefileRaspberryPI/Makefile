# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef PKG_CONFIG
  PKG_CONFIG=pkg-config
endif

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

JUCE_ARCH_LABEL := $(shell uname -m)

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DSAF_IPP_LIB=\"C:\Users\Micha\source\repos\Spatial_Audio_Framework\dependencies\Win64\lib\saf_ipp_custom.lib\";" "-DSAF_MKL_LIB=\"C:\Users\Micha\source\repos\Spatial_Audio_Framework\dependencies\Win64\lib\saf_mkl_custom_lp64.lib\";" "-DSAF_USE_OPEN_BLAS_AND_LAPACKE" "-DSAF_ENABLE_SOFA_READER_MODULE" "-DJUCER_LINUX_MAKE_94E17606=1" "-DJUCE_APP_VERSION=0.1.1" "-DJUCE_APP_VERSION_HEX=0x101" $(shell $(PKG_CONFIG) --cflags alsa freetype2 gl libcurl) -pthread -I../../../../SDKs/JUCE/modules/juce_audio_processors/format_types/VST3_SDK -I../../JuceLibraryCode -I../../../../SDKs/JUCE/modules -I../../../../SDKs/Spatial_Audio_Framework/framework/include -I../../../../SDKs/Spatial_Audio_Framework/examples/include -I../../../../SDKs/VST2_SDK -I/usr/include -I/usr/include/arm-linux-gnueabihf -IC:/Users/Micha/source/repos/SPARTA-master/SDKs/Spatial_Audio_Framework/examples/include -IC:/Users/Micha/source/repos/Spatial_Audio_Framework/framework/include -IC:/Users/Micha/source/repos/Spatial_Audio_Framework/examples/src/binauraliser_nf $(CPPFLAGS)

  JUCE_CPPFLAGS_VST :=  "-DJucePlugin_Build_VST=1" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := sparta_binauraliser_nf_debug.so
  JUCE_VSTDESTDIR := $(HOME)/.vst
  JUCE_COPYCMD_VST := $(JUCE_OUTDIR)/sparta_binauraliser_nf_debug.so $(JUCE_VSTDESTDIR)

  JUCE_CPPFLAGS_VST3 :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_CFLAGS_VST3 := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST3 := -shared -Wl,--no-undefined
  JUCE_VST3DIR := sparta_binauraliser_nf_debug.vst3
  VST3_PLATFORM_ARCH := $(shell $(CXX) make_helpers/arch_detection.cpp 2>&1 | tr '\n' ' ' | sed "s/.*JUCE_ARCH \([a-zA-Z0-9_-]*\).*/\1/")
  JUCE_VST3SUBDIR := Contents/$(VST3_PLATFORM_ARCH)-linux
  JUCE_TARGET_VST3 := $(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)/sparta_binauraliser_nf_debug.so
  JUCE_VST3DESTDIR := $(HOME)/.vst3
  JUCE_COPYCMD_VST3 := $(JUCE_OUTDIR)/$(JUCE_VST3DIR) $(JUCE_VST3DESTDIR)

  JUCE_CPPFLAGS_STANDALONE_PLUGIN :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=1" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_STANDALONE_PLUGIN := sparta_binauraliser_nf_debug

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=1" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=1" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0" "-DJUCE_SHARED_CODE=1"
  JUCE_CFLAGS_SHARED_CODE := -fPIC -fvisibility=hidden
  JUCE_TARGET_SHARED_CODE := sparta_binauraliser_nf_debug.a

  JUCE_CPPFLAGS_VST3_MANIFEST_HELPER :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_VST3_MANIFEST_HELPER := juce_vst3_helper

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -g -ggdb -O0 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell $(PKG_CONFIG) --libs alsa freetype2 gl libcurl) -fvisibility=hidden -L/usr/lib/arm-linux-gnueabihf -lopenblas -llapacke -lnetcdf -lrt -ldl -lpthread $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(JUCE_TARGET_VST) $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3) $(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3_MANIFEST_HELPER) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DSAF_IPP_LIB=\"C:\Users\Micha\source\repos\Spatial_Audio_Framework\dependencies\Win64\lib\saf_ipp_custom.lib\";" "-DSAF_MKL_LIB=\"C:\Users\Micha\source\repos\Spatial_Audio_Framework\dependencies\Win64\lib\saf_mkl_custom_lp64.lib\";" "-DSAF_USE_OPEN_BLAS_AND_LAPACKE" "-DSAF_ENABLE_SOFA_READER_MODULE" "-DJUCER_LINUX_MAKE_94E17606=1" "-DJUCE_APP_VERSION=0.1.1" "-DJUCE_APP_VERSION_HEX=0x101" $(shell $(PKG_CONFIG) --cflags alsa freetype2 gl libcurl) -pthread -I../../../../SDKs/JUCE/modules/juce_audio_processors/format_types/VST3_SDK -I../../JuceLibraryCode -I../../../../SDKs/JUCE/modules -I../../../../SDKs/Spatial_Audio_Framework/framework/include -I../../../../SDKs/Spatial_Audio_Framework/examples/include -I../../../../SDKs/VST2_SDK -I/usr/include -I/usr/include/arm-linux-gnueabihf -IC:/Users/Micha/source/repos/SPARTA-master/SDKs/Spatial_Audio_Framework/examples/include -IC:/Users/Micha/source/repos/Spatial_Audio_Framework/framework/include -IC:/Users/Micha/source/repos/Spatial_Audio_Framework/examples/src/binauraliser_nf $(CPPFLAGS)

  JUCE_CPPFLAGS_VST :=  "-DJucePlugin_Build_VST=1" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := sparta_binauraliser_nf.so
  JUCE_VSTDESTDIR := $(HOME)/.vst
  JUCE_COPYCMD_VST := $(JUCE_OUTDIR)/sparta_binauraliser_nf.so $(JUCE_VSTDESTDIR)

  JUCE_CPPFLAGS_VST3 :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_CFLAGS_VST3 := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST3 := -shared -Wl,--no-undefined
  JUCE_VST3DIR := sparta_binauraliser_nf.vst3
  VST3_PLATFORM_ARCH := $(shell $(CXX) make_helpers/arch_detection.cpp 2>&1 | tr '\n' ' ' | sed "s/.*JUCE_ARCH \([a-zA-Z0-9_-]*\).*/\1/")
  JUCE_VST3SUBDIR := Contents/$(VST3_PLATFORM_ARCH)-linux
  JUCE_TARGET_VST3 := $(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)/sparta_binauraliser_nf.so
  JUCE_VST3DESTDIR := $(HOME)/.vst3
  JUCE_COPYCMD_VST3 := $(JUCE_OUTDIR)/$(JUCE_VST3DIR) $(JUCE_VST3DESTDIR)

  JUCE_CPPFLAGS_STANDALONE_PLUGIN :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=1" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_STANDALONE_PLUGIN := sparta_binauraliser_nf

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=1" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=1" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0" "-DJUCE_SHARED_CODE=1"
  JUCE_CFLAGS_SHARED_CODE := -fPIC -fvisibility=hidden
  JUCE_TARGET_SHARED_CODE := sparta_binauraliser_nf.a

  JUCE_CPPFLAGS_VST3_MANIFEST_HELPER :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_VST3_MANIFEST_HELPER := juce_vst3_helper

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell $(PKG_CONFIG) --libs alsa freetype2 gl libcurl) -fvisibility=hidden -L/usr/lib/arm-linux-gnueabihf -lopenblas -llapacke -lnetcdf -lrt -ldl -lpthread $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(JUCE_TARGET_VST) $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3) $(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3_MANIFEST_HELPER) $(JUCE_OBJDIR)
endif

OBJECTS_ALL := \

OBJECTS_VST := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_dd551e08.o \

OBJECTS_VST3 := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST3_dd633589.o \

OBJECTS_STANDALONE_PLUGIN := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_Standalone_1a871192.o \

OBJECTS_SHARED_CODE := \
  $(JUCE_OBJDIR)/DiffuseFieldProcessor_744eb444.o \
  $(JUCE_OBJDIR)/DelayProcessorLagrange_4678ccda.o \
  $(JUCE_OBJDIR)/inputCoordsView_9cb3c537.o \
  $(JUCE_OBJDIR)/pannerView_14409603.o \
  $(JUCE_OBJDIR)/PluginEditor_758fa7c0.o \
  $(JUCE_OBJDIR)/PluginProcessor_9be2e769.o \
  $(JUCE_OBJDIR)/binauraliser_6882fb77.o \
  $(JUCE_OBJDIR)/binauraliser_internal_425383cf.o \
  $(JUCE_OBJDIR)/binauraliser_nf_70b84c95.o \
  $(JUCE_OBJDIR)/binauraliser_nf_internal_83249471.o \
  $(JUCE_OBJDIR)/saf_cdf4sap_fcdc8d1a.o \
  $(JUCE_OBJDIR)/saf_hoa_e8f374e8.o \
  $(JUCE_OBJDIR)/saf_hoa_internal_cac6197e.o \
  $(JUCE_OBJDIR)/saf_default_hrirs_2bfe5f3f.o \
  $(JUCE_OBJDIR)/saf_hrir_4256d9c0.o \
  $(JUCE_OBJDIR)/saf_reverb_daf61920.o \
  $(JUCE_OBJDIR)/saf_reverb_internal_778cb446.o \
  $(JUCE_OBJDIR)/saf_sh_671adec0.o \
  $(JUCE_OBJDIR)/saf_sh_internal_85dc42a6.o \
  $(JUCE_OBJDIR)/hdf_dataobject_84a0632f.o \
  $(JUCE_OBJDIR)/hdf_fractalhead_374bf815.o \
  $(JUCE_OBJDIR)/hdf_reader_2f5cd289.o \
  $(JUCE_OBJDIR)/kdtree_3ca1188.o \
  $(JUCE_OBJDIR)/mysofa_internal_e2184a12.o \
  $(JUCE_OBJDIR)/mysofa_b2e91fee.o \
  $(JUCE_OBJDIR)/saf_sofa_reader_a177bfca.o \
  $(JUCE_OBJDIR)/saf_tracker_132417e4.o \
  $(JUCE_OBJDIR)/saf_tracker_internal_8771202.o \
  $(JUCE_OBJDIR)/saf_utility_dvf_34b59b26.o \
  $(JUCE_OBJDIR)/saf_utility_bessel_2ad7bec9.o \
  $(JUCE_OBJDIR)/saf_utility_complex_910ce25b.o \
  $(JUCE_OBJDIR)/saf_utility_decor_728d3350.o \
  $(JUCE_OBJDIR)/saf_utility_fft_bf3ba35f.o \
  $(JUCE_OBJDIR)/saf_utility_filters_b0237ae6.o \
  $(JUCE_OBJDIR)/saf_utility_geometry_bcf84cf1.o \
  $(JUCE_OBJDIR)/saf_utility_latticeCoeffs_2339101b.o \
  $(JUCE_OBJDIR)/saf_utility_loudspeaker_presets_f06023cd.o \
  $(JUCE_OBJDIR)/saf_utility_matrixConv_7ef9fd4.o \
  $(JUCE_OBJDIR)/saf_utility_misc_345547eb.o \
  $(JUCE_OBJDIR)/saf_utility_pitch_f515526b.o \
  $(JUCE_OBJDIR)/saf_utility_qmf_bfd99ff5.o \
  $(JUCE_OBJDIR)/saf_utility_sensorarray_presets_b2f887bf.o \
  $(JUCE_OBJDIR)/saf_utility_sort_3ee6b41d.o \
  $(JUCE_OBJDIR)/saf_utility_veclib_2cc0bdb0.o \
  $(JUCE_OBJDIR)/saf_vbap_a1fd46c0.o \
  $(JUCE_OBJDIR)/saf_vbap_internal_3f2edaa6.o \
  $(JUCE_OBJDIR)/afSTFT_internal_477ac9c8.o \
  $(JUCE_OBJDIR)/afSTFTlib_53a89331.o \
  $(JUCE_OBJDIR)/convhull_3d_6ea2ea7e.o \
  $(JUCE_OBJDIR)/kiss_fft_7a7b7f87.o \
  $(JUCE_OBJDIR)/kiss_fftr_d4f56a95.o \
  $(JUCE_OBJDIR)/md_malloc_f5f270c0.o \
  $(JUCE_OBJDIR)/resample_5e67d096.o \
  $(JUCE_OBJDIR)/adler32_e6cadf6c.o \
  $(JUCE_OBJDIR)/compress_eab98e55.o \
  $(JUCE_OBJDIR)/crc32_18ea9baa.o \
  $(JUCE_OBJDIR)/deflate_d9349e22.o \
  $(JUCE_OBJDIR)/infback_545d42ff.o \
  $(JUCE_OBJDIR)/inffast_5b380d34.o \
  $(JUCE_OBJDIR)/inflate_65755cfe.o \
  $(JUCE_OBJDIR)/inftrees_c981bc7.o \
  $(JUCE_OBJDIR)/trees_9c68688c.o \
  $(JUCE_OBJDIR)/uncompr_bfbde281.o \
  $(JUCE_OBJDIR)/zutil_dfc16db3.o \
  $(JUCE_OBJDIR)/BinaryData_ce4232d4.o \
  $(JUCE_OBJDIR)/BinaryData2_fa243da8.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o \
  $(JUCE_OBJDIR)/include_juce_audio_devices_63111d02.o \
  $(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_ARA_31a052ed.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_ara_2a4c6ef7.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_lv2_libs_12bdca08.o \
  $(JUCE_OBJDIR)/include_juce_audio_utils_9f9fb2d6.o \
  $(JUCE_OBJDIR)/include_juce_core_f26d17db.o \
  $(JUCE_OBJDIR)/include_juce_cryptography_8cb807a8.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o \
  $(JUCE_OBJDIR)/include_juce_dsp_aeb2060f.o \
  $(JUCE_OBJDIR)/include_juce_events_fd7d695.o \
  $(JUCE_OBJDIR)/include_juce_graphics_f817e147.o \
  $(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o \
  $(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o \
  $(JUCE_OBJDIR)/include_juce_opengl_a8a032b.o \
  $(JUCE_OBJDIR)/include_juce_osc_f3df604d.o \

OBJECTS_VST3_MANIFEST_HELPER := \
  $(JUCE_OBJDIR)/juce_VST3ManifestHelper_60eeacec.o \

.PHONY: clean all strip VST VST3 Standalone VST3_MANIFEST_HELPER

all : VST VST3 Standalone VST3_MANIFEST_HELPER

VST : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST)
VST3 : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3)
Standalone : $(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN)
VST3_MANIFEST_HELPER : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3_MANIFEST_HELPER)


$(JUCE_OUTDIR)/$(JUCE_TARGET_VST) : $(OBJECTS_VST) $(JUCE_OBJDIR)/execinfo.cmd $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 gl libcurl
	@echo Linking "based_on_sparta_binauraliser_nf - VST"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST) $(OBJECTS_VST) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(shell cat $(JUCE_OBJDIR)/execinfo.cmd) $(JUCE_LDFLAGS_VST) $(RESOURCES) $(TARGET_ARCH)
	-$(V_AT)[ ! "$(JUCE_VSTDESTDIR)" ]  || (mkdir -p $(JUCE_VSTDESTDIR)  && cp -R $(JUCE_COPYCMD_VST))

$(JUCE_OUTDIR)/$(JUCE_TARGET_VST3) : $(OBJECTS_VST3) $(JUCE_OBJDIR)/execinfo.cmd $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3_MANIFEST_HELPER)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 gl libcurl
	@echo Linking "based_on_sparta_binauraliser_nf - VST3"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)/$(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3) $(OBJECTS_VST3) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(shell cat $(JUCE_OBJDIR)/execinfo.cmd) $(JUCE_LDFLAGS_VST3) $(RESOURCES) $(TARGET_ARCH)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)/$(JUCE_VST3DIR)/Contents/Resources
	-$(V_AT)rm -f $(JUCE_OUTDIR)/$(JUCE_VST3DIR)/Contents/moduleinfo.json
	$(V_AT) $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3_MANIFEST_HELPER) -create -version "0.1.1" -path $(JUCE_OUTDIR)/$(JUCE_VST3DIR) -output $(JUCE_OUTDIR)/$(JUCE_VST3DIR)/Contents/Resources/moduleinfo.json
	-$(V_AT)[ ! "$(JUCE_VST3DESTDIR)" ] || (mkdir -p $(JUCE_VST3DESTDIR) && cp -R $(JUCE_COPYCMD_VST3))

$(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN) : $(OBJECTS_STANDALONE_PLUGIN) $(JUCE_OBJDIR)/execinfo.cmd $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 gl libcurl
	@echo Linking "based_on_sparta_binauraliser_nf - Standalone Plugin"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN) $(OBJECTS_STANDALONE_PLUGIN) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(shell cat $(JUCE_OBJDIR)/execinfo.cmd) $(JUCE_LDFLAGS_STANDALONE_PLUGIN) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) : $(OBJECTS_SHARED_CODE) $(JUCE_OBJDIR)/execinfo.cmd $(RESOURCES)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 gl libcurl
	@echo Linking "based_on_sparta_binauraliser_nf - Shared Code"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(AR) -rcs $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(OBJECTS_SHARED_CODE)

$(JUCE_OUTDIR)/$(JUCE_TARGET_VST3_MANIFEST_HELPER) : $(OBJECTS_VST3_MANIFEST_HELPER) $(JUCE_OBJDIR)/execinfo.cmd $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_OBJDIR)/cxxfs.cmd
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 gl libcurl
	@echo Linking "based_on_sparta_binauraliser_nf - VST3 Manifest Helper"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3_MANIFEST_HELPER) $(OBJECTS_VST3_MANIFEST_HELPER) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(shell cat $(JUCE_OBJDIR)/execinfo.cmd) $(shell cat $(JUCE_OBJDIR)/cxxfs.cmd) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_dd551e08.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_VST2.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_plugin_client_VST2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST) $(JUCE_CFLAGS_VST) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST3_dd633589.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_plugin_client_VST3.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST3) $(JUCE_CFLAGS_VST3) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_Standalone_1a871192.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_Standalone.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_plugin_client_Standalone.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_STANDALONE_PLUGIN) $(JUCE_CFLAGS_STANDALONE_PLUGIN) -o "$@" -c "$<"

$(JUCE_OBJDIR)/DiffuseFieldProcessor_744eb444.o: ../../src/DiffuseFieldProcessor.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling DiffuseFieldProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/DelayProcessorLagrange_4678ccda.o: ../../src/DelayProcessorLagrange.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling DelayProcessorLagrange.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/inputCoordsView_9cb3c537.o: ../../src/inputCoordsView.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling inputCoordsView.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pannerView_14409603.o: ../../src/pannerView.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pannerView.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditor_758fa7c0.o: ../../src/PluginEditor.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling PluginEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessor_9be2e769.o: ../../src/PluginProcessor.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling PluginProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/binauraliser_6882fb77.o: ../../../../../Spatial_Audio_Framework/examples/src/binauraliser/binauraliser.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling binauraliser.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/binauraliser_internal_425383cf.o: ../../../../../Spatial_Audio_Framework/examples/src/binauraliser/binauraliser_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling binauraliser_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/binauraliser_nf_70b84c95.o: ../../../../../Spatial_Audio_Framework/examples/src/binauraliser_nf/binauraliser_nf.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling binauraliser_nf.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/binauraliser_nf_internal_83249471.o: ../../../../../Spatial_Audio_Framework/examples/src/binauraliser_nf/binauraliser_nf_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling binauraliser_nf_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_cdf4sap_fcdc8d1a.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_cdf4sap/saf_cdf4sap.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_cdf4sap.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hoa_e8f374e8.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hoa/saf_hoa.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_hoa.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hoa_internal_cac6197e.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hoa/saf_hoa_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_hoa_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_default_hrirs_2bfe5f3f.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hrir/saf_default_hrirs.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_default_hrirs.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hrir_4256d9c0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hrir/saf_hrir.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_hrir.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_reverb_daf61920.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_reverb/saf_reverb.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_reverb.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_reverb_internal_778cb446.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_reverb/saf_reverb_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_reverb_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sh_671adec0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sh/saf_sh.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_sh.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sh_internal_85dc42a6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sh/saf_sh_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_sh_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hdf_dataobject_84a0632f.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sofa_reader/libmysofa/internal/hdf_dataobject.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling hdf_dataobject.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hdf_fractalhead_374bf815.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sofa_reader/libmysofa/internal/hdf_fractalhead.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling hdf_fractalhead.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hdf_reader_2f5cd289.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sofa_reader/libmysofa/internal/hdf_reader.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling hdf_reader.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/kdtree_3ca1188.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sofa_reader/libmysofa/internal/kdtree.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling kdtree.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mysofa_internal_e2184a12.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sofa_reader/libmysofa/internal/mysofa_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling mysofa_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mysofa_b2e91fee.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sofa_reader/libmysofa/mysofa.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling mysofa.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sofa_reader_a177bfca.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sofa_reader/saf_sofa_reader.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_sofa_reader.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_tracker_132417e4.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_tracker/saf_tracker.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_tracker.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_tracker_internal_8771202.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_tracker/saf_tracker_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_tracker_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_dvf_34b59b26.o: ../../../../../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_dvf.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_dvf.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_bessel_2ad7bec9.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_bessel.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_bessel.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_complex_910ce25b.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_complex.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_complex.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_decor_728d3350.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_decor.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_decor.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_fft_bf3ba35f.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_fft.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_fft.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_filters_b0237ae6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_filters.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_filters.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_geometry_bcf84cf1.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_geometry.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_geometry.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_latticeCoeffs_2339101b.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_latticeCoeffs.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_latticeCoeffs.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_loudspeaker_presets_f06023cd.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_loudspeaker_presets.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_loudspeaker_presets.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_matrixConv_7ef9fd4.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_matrixConv.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_matrixConv.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_misc_345547eb.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_misc.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_misc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_pitch_f515526b.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_pitch.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_pitch.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_qmf_bfd99ff5.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_qmf.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_qmf.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_sensorarray_presets_b2f887bf.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_sensorarray_presets.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_sensorarray_presets.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_sort_3ee6b41d.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_sort.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_sort.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_utility_veclib_2cc0bdb0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_veclib.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_utility_veclib.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_vbap_a1fd46c0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_vbap/saf_vbap.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_vbap.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_vbap_internal_3f2edaa6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_vbap/saf_vbap_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling saf_vbap_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/afSTFT_internal_477ac9c8.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/afSTFT/afSTFT_internal.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling afSTFT_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/afSTFTlib_53a89331.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/afSTFT/afSTFTlib.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling afSTFTlib.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/convhull_3d_6ea2ea7e.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/convhull_3d/convhull_3d.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling convhull_3d.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/kiss_fft_7a7b7f87.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/kissFFT/kiss_fft.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling kiss_fft.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/kiss_fftr_d4f56a95.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/kissFFT/kiss_fftr.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling kiss_fftr.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/md_malloc_f5f270c0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/md_malloc/md_malloc.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling md_malloc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/resample_5e67d096.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/speex_resampler/resample.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling resample.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/adler32_e6cadf6c.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/adler32.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling adler32.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/compress_eab98e55.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/compress.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling compress.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/crc32_18ea9baa.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/crc32.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling crc32.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/deflate_d9349e22.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/deflate.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling deflate.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/infback_545d42ff.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/infback.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling infback.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/inffast_5b380d34.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/inffast.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling inffast.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/inflate_65755cfe.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/inflate.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling inflate.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/inftrees_c981bc7.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/inftrees.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling inftrees.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trees_9c68688c.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/trees.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling trees.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/uncompr_bfbde281.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/uncompr.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling uncompr.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/zutil_dfc16db3.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/zlib/zutil.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling zutil.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling BinaryData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData2_fa243da8.o: ../../JuceLibraryCode/BinaryData2.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling BinaryData2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o: ../../JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_devices_63111d02.o: ../../JuceLibraryCode/include_juce_audio_devices.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o: ../../JuceLibraryCode/include_juce_audio_formats.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_ARA_31a052ed.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_ARA.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_plugin_client_ARA.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o: ../../JuceLibraryCode/include_juce_audio_processors.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_ara_2a4c6ef7.o: ../../JuceLibraryCode/include_juce_audio_processors_ara.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_processors_ara.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_lv2_libs_12bdca08.o: ../../JuceLibraryCode/include_juce_audio_processors_lv2_libs.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_processors_lv2_libs.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_utils_9f9fb2d6.o: ../../JuceLibraryCode/include_juce_audio_utils.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_f26d17db.o: ../../JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_cryptography_8cb807a8.o: ../../JuceLibraryCode/include_juce_cryptography.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_cryptography.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o: ../../JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_dsp_aeb2060f.o: ../../JuceLibraryCode/include_juce_dsp.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_dsp.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_fd7d695.o: ../../JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_graphics_f817e147.o: ../../JuceLibraryCode/include_juce_graphics.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o: ../../JuceLibraryCode/include_juce_gui_basics.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o: ../../JuceLibraryCode/include_juce_gui_extra.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_opengl_a8a032b.o: ../../JuceLibraryCode/include_juce_opengl.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_opengl.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_osc_f3df604d.o: ../../JuceLibraryCode/include_juce_osc.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_osc.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_VST3ManifestHelper_60eeacec.o: ../../../../SDKs/JUCE/modules/juce_audio_plugin_client/VST3/juce_VST3ManifestHelper.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling juce_VST3ManifestHelper.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST3_MANIFEST_HELPER) $(JUCE_CFLAGS_VST3_MANIFEST_HELPER) -o "$@" -c "$<"

$(JUCE_OBJDIR)/execinfo.cmd:
	-$(V_AT)mkdir -p $(@D)
	-@if [ -z "$(V_AT)" ]; then echo "Checking if we need to link libexecinfo"; fi
	$(V_AT)printf "int main() { return 0; }" | $(CXX) -x c++ -o $(@D)/execinfo.x -lexecinfo - >/dev/null 2>&1 && printf -- "-lexecinfo" > "$@" || touch "$@"

$(JUCE_OBJDIR)/cxxfs.cmd:
	-$(V_AT)mkdir -p $(@D)
	-@if [ -z "$(V_AT)" ]; then echo "Checking if we need to link stdc++fs"; fi
	$(V_AT)printf "int main() { return 0; }" | $(CXX) -x c++ -o $(@D)/cxxfs.x -lstdc++fs - >/dev/null 2>&1 && printf -- "-lstdc++fs" > "$@" || touch "$@"

clean:
	@echo Cleaning based_on_sparta_binauraliser_nf
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping based_on_sparta_binauraliser_nf
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(JUCE_TARGET_VST)
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3)
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN)
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3_MANIFEST_HELPER)

-include $(OBJECTS_VST:%.o=%.d)
-include $(OBJECTS_VST3:%.o=%.d)
-include $(OBJECTS_STANDALONE_PLUGIN:%.o=%.d)
-include $(OBJECTS_SHARED_CODE:%.o=%.d)
-include $(OBJECTS_VST3_MANIFEST_HELPER:%.o=%.d)
