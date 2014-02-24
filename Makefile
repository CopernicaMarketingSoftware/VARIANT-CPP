PREFIX			=	/usr
INCLUDE_DIR		=	${PREFIX}/include/
LIBRARY_DIR		=	${PREFIX}/lib/

all:
		$(MAKE) -C src all

clean:
		$(MAKE) -C src clean

install:
		mkdir -p ${INCLUDE_DIR}/variant
		mkdir -p ${LIBRARY_DIR}
		cp -f variant.h ${INCLUDE_DIR}
		cp -f include/*.h ${INCLUDE_DIR}/variant
		cp -f src/libvariant.so ${LIBRARY_DIR}
