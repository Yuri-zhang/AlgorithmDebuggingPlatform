add_rules("mode.debug", "mode.release")

target("foo")
    set_kind("shared")
    add_files("src/foo.cpp")
    add_includedirs("D:/AlgorithmDebuggingPlatform/Opencv/include/opencv2")
    add_includedirs("D:/AlgorithmDebuggingPlatform/Opencv/include")
    add_linkdirs("D:/AlgorithmDebuggingPlatform/Opencv/lib/release")
    add_links("opencv_bgsegm430")
    add_links("opencv_bioinspired430")
    add_links("opencv_calib3d430")
    add_links("opencv_ccalib430")
    add_links("opencv_core430")
    add_links("opencv_datasets430")
    add_links("opencv_dnn_objdetect430")
    add_links("opencv_dnn_superres430")
    add_links("opencv_dnn430")
    add_links("opencv_dpm430")
    add_links("opencv_face430")
    add_links("opencv_features2d430")
    add_links("opencv_flann430")
    add_links("opencv_fuzzy430")
    add_links("opencv_gapi430")
    add_links("opencv_hfs430")
    add_links("opencv_highgui430")
    add_links("opencv_img_hash430")
    add_links("opencv_imgcodecs430")
    add_links("opencv_imgproc430")
    add_links("opencv_intensity_transform430")
    add_links("opencv_line_descriptor430")
    add_links("opencv_ml430")
    add_links("opencv_objdetect430")
    add_links("opencv_optflow430")
    add_links("opencv_phase_unwrapping430")
    add_links("opencv_photo430")
    add_links("opencv_plot430")
    add_links("opencv_quality430")
    add_links("opencv_rapid430")
    add_links("opencv_reg430")
    add_links("opencv_rgbd430")
    add_links("opencv_saliency430")
    add_links("opencv_shape430")
    add_links("opencv_stereo430")
    add_links("opencv_stitching430")
    add_links("opencv_structured_light430")
    add_links("opencv_superres430")
    add_links("opencv_surface_matching430")
    add_links("opencv_text430")
    add_links("opencv_tracking430")
    add_links("opencv_video430")
    add_links("opencv_videoio430")
    add_links("opencv_videostab430")
    add_links("opencv_xfeatures2d430")
    add_links("opencv_ximgproc430")
    add_links("opencv_xobjdetect430")
    add_links("opencv_xphoto430")

target("test")
    set_kind("binary")
    add_deps("foo")
    add_files("src/main.cpp")
    add_includedirs("D://AlgorithmDebuggingPlatform//Opencv//include//opencv2")
    add_includedirs("D://AlgorithmDebuggingPlatform//Opencv//include")
    add_linkdirs("D://AlgorithmDebuggingPlatform//Opencv//lib//release")
    add_links("opencv_bgsegm430")
    add_links("opencv_bioinspired430")
    add_links("opencv_calib3d430")
    add_links("opencv_ccalib430")
    add_links("opencv_core430")
    add_links("opencv_datasets430")
    add_links("opencv_dnn_objdetect430")
    add_links("opencv_dnn_superres430")
    add_links("opencv_dnn430")
    add_links("opencv_dpm430")
    add_links("opencv_face430")
    add_links("opencv_features2d430")
    add_links("opencv_flann430")
    add_links("opencv_fuzzy430")
    add_links("opencv_gapi430")
    add_links("opencv_hfs430")
    add_links("opencv_highgui430")
    add_links("opencv_img_hash430")
    add_links("opencv_imgcodecs430")
    add_links("opencv_imgproc430")
    add_links("opencv_intensity_transform430")
    add_links("opencv_line_descriptor430")
    add_links("opencv_ml430")
    add_links("opencv_objdetect430")
    add_links("opencv_optflow430")
    add_links("opencv_phase_unwrapping430")
    add_links("opencv_photo430")
    add_links("opencv_plot430")
    add_links("opencv_quality430")
    add_links("opencv_rapid430")
    add_links("opencv_reg430")
    add_links("opencv_rgbd430")
    add_links("opencv_saliency430")
    add_links("opencv_shape430")
    add_links("opencv_stereo430")
    add_links("opencv_stitching430")
    add_links("opencv_structured_light430")
    add_links("opencv_superres430")
    add_links("opencv_surface_matching430")
    add_links("opencv_text430")
    add_links("opencv_tracking430")
    add_links("opencv_video430")
    add_links("opencv_videoio430")
    add_links("opencv_videostab430")
    add_links("opencv_xfeatures2d430")
    add_links("opencv_ximgproc430")
    add_links("opencv_xobjdetect430")
    add_links("opencv_xphoto430")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

