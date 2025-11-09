.PHONY: git-submodule-init, git-submodule-update, vial-qmk-clean, vial-qmk-init, vial-qmk-compile, vial-qmk-flash, vial-qmk-init-all, vial-qmk-compile-all, update-all, vial-corne41

KB := crkbd
KR := rev4_1
KM := vial

git-submodule-init:
	git submodule update --remote
	git submodule update --init --recursive
	cd src/vial-kb/vial-qmk; git submodule add https://github.com/getreuer/qmk-modules.git modules/getreuer

git-submodule-update:
	git submodule update --remote --recursive

vial-qmk-clean:
	rm -rf src/vial-kb/vial-qmk/keyboards/tmp
	cd src/vial-kb/vial-qmk; qmk clean

vial-qmk-init:
	$(eval KB := ${kb})
	rm -rf src/vial-kb/vial-qmk/keyboards/tmp/${KB}
	mkdir -p src/vial-kb/vial-qmk/keyboards/tmp/${KB}
	cp -r $(shell pwd)/keyboards/${KB}/qmk/qmk_firmware/* src/vial-kb/vial-qmk/keyboards/tmp/${KB}
	rm -rf src/vial-kb/vial-qmk/keyboards/tmp/${KB}/keymaps
	ln -s $(shell pwd)/keyboards/${KB}/vial-kb/vial-qmk/keymaps src/vial-kb/vial-qmk/keyboards/tmp/${KB}/keymaps
	mkdir -p keyboards/${KB}/vial-kb/vial-qmk/.build

vial-qmk-compile:
	$(eval KB := ${kb})
	$(eval KR := ${kr})
	$(eval KM := ${km})
	$(eval FILE := $(shell echo "${kb}_${kr}_${km}" | sed 's/\//_/'))
	cd src/vial-kb/vial-qmk; qmk compile -kb tmp/${KB}/${KR} -km ${KM}
	cp -f src/vial-kb/vial-qmk/.build/tmp_${FILE}.uf2 keyboards/${KB}/vial-kb/vial-qmk/.build/${FILE}.uf2 | true

vial-qmk-flash:
	$(eval KB := ${kb})
	$(eval KR := ${kr})
	$(eval KM := ${km})
	cd src/vial-kb/vial-qmk; qmk flash -kb tmp/${KB}/${KR} -km ${KM}

vial-qmk-init-all:
	kb=crkbd make vial-qmk-init

vial-qmk-compile-all:
	kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-compile

update-all:
	make vial-qmk-clean
	make vial-qmk-init-all
	make vial-qmk-compile-all

vial-corne41:
	make vial-qmk-clean
	kb=crkbd make vial-qmk-init
	kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-compile
	$(eval FILE := $(shell echo "${KB}_${KR}_standard_${KM}" | sed 's/\//_/'))
	cp keyboards/crkbd/vial-kb/vial-qmk/.build/${FILE}.uf2 ${FILE}_$(shell date +%F_%R).uf2 | true

