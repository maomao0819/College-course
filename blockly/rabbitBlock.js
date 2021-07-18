Blockly.Blocks['go-right'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_CENTRE)
        .appendField("Go Right");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};
Blockly.Blocks['go-left'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_CENTRE)
        .appendField("Go Left");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};
Blockly.Blocks['go-up'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_CENTRE)
        .appendField("Go Up");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};
Blockly.Blocks['go-down'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_CENTRE)
        .appendField("Go Down");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

goog.provide('Blockly.JavaScript.go-right');
goog.provide('Blockly.JavaScript.go-left');
goog.provide('Blockly.JavaScript.go-up');
goog.provide('Blockly.JavaScript.go-down');

Blockly.JavaScript['go-right'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code = 'rabbitDraw(RIGHT);';
  return code;
};
Blockly.JavaScript['go-down'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code = 'rabbitDraw(DOWN);';
  return code;
};
Blockly.JavaScript['go-left'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code = 'rabbitDraw(LEFT);';
  return code;
};
Blockly.JavaScript['go-up'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code = 'rabbitDraw(UP);';
  return code;
};

