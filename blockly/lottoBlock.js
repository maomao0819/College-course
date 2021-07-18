Blockly.Blocks['lottoblock'] = {
  init: function() {
    this.appendValueInput("speech")
        .setCheck("String")
        .appendField(new Blockly.FieldTextInput("read the text"), "label");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};
goog.provide('Blockly.JavaScript.lottoblock');

Blockly.JavaScript['lottoblock'] = function(block) {
  var text_lotto = block.getFieldValue('label');
  var value_speech = Blockly.JavaScript.valueToCode(block, 'speech', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var code = 'speak(' + value_speech +');\n';
  //var code = 'speak("早安");';
  return code;
};

function speak(word) {
	/*var i, node;                                         		//配合html使用<div class ="lotto"></div>;
	var arr = word.split(",");
	var aDiv = document.getElementsByClassName("lotto");
	for(i=0; i<6; i++) {
		node = document.createTextNode(arr[i]);
		aDiv[i].appendChild(node);
	}*/
	document.getElementById("lottoNumber").innerHTML = "<marquee>" + word + "</marquee>";
	document.getElementById("speaker").autoplay = true;
	document.getElementById("speaker").src="https://translate.google.com/translate_tts?ie=utf-8&tl=zh-tw&client=tw-ob&q=" + word;
	//document.getElementById("speaker").play();
}