.PHONY: clean All

All:
	@echo "----------Building project:[ misja008_drone_io - Debug ]----------"
	@cd "misja008_drone_io" && "$(MAKE)" -f  "misja008_drone_io.mk" && "$(MAKE)" -f  "misja008_drone_io.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ misja008_drone_io - Debug ]----------"
	@cd "misja008_drone_io" && "$(MAKE)" -f  "misja008_drone_io.mk" clean
