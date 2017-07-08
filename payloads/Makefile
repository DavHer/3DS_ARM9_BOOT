dir_out := out

all: $(dir_out) stage1 stage2

$(dir_out):
	@mkdir -p $(dir_out)


.PHONY: stage1
stage1: $(dir_out) 
	@$(MAKE) -C payload_stage1

.PHONY: stage2
stage2: $(dir_out) 
	@$(MAKE) -C payload_stage2

clean:
	@$(MAKE) -C payload_stage1 clean
	@$(MAKE) -C payload_stage2 clean
