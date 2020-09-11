#########################################################################
# Master makefile


.PHONY: all clean

working_dir	:= ${shell pwd}
INSTALLDIR=${working_dir}

MY_MAKE_FLAGS ?=
MY_CMAKE_FLAGS ?= -g3


# Set up variables holding the names of platform-dependent directories --
# set these after evaluating site-specific instructions
build_dir     := build
dist_dir      := .

$(info dist_dir = ${dist_dir})
$(info INSTALLDIR = ${INSTALLDIR})


#########################################################################
# Targets

all: dist

# 'make cmakesetup' constructs the build directory and runs 'cmake' there,
# generating makefiles to build the project.  For speed, it only does this when
# ${build_dir}/Makefile doesn't already exist, in which case we rely on the
# cmake generated makefiles to regenerate themselves when necessary.
cmakesetup:
	@ (if [ ! -e ${build_dir}/Makefile ] ; then \
	        cmake -E make_directory ${build_dir} ; \
		cd ${build_dir} ; \
		cmake -DCMAKE_INSTALL_PREFIX=${INSTALLDIR}/${dist_dir} \
			${MY_CMAKE_FLAGS} \
			../src ; \
	 fi)

# 'make cmake' does a basic build (after first setting it up)
cmake: cmakesetup
	( cd ${build_dir} ; ${MAKE} ${MY_MAKE_FLAGS} )

# 'make cmakeinstall' builds everthing and installs it in 'dist'
cmakeinstall: cmake
	( cd ${build_dir} ; ${MAKE} ${MY_MAKE_FLAGS} install )

# 'make dist' is just a synonym for 'make cmakeinstall'
dist : cmakeinstall

# 'make clean' clears out the build directory for this platform
clean:
	cmake -E remove_directory ${build_dir} ; \
	rm dragonscurse
	rm tmx2bin

