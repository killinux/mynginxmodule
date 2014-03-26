function KeyEventDetail(){
    this.inputchar='';
	this.isSpecial=false;
	this.isSupport=true;
	this.isControl=false;
	this.isShift=false;
	this.getSendCmd=function(){
		var sendStrTemp=String(this.inputchar);
		if(this.isSpecial){
			var flag=this.inputchar;
			switch (flag){
				case Terminal.prototype.globals.termKey.CR:
					sendStrTemp=String(this.inputchar);
					break;
				case Terminal.prototype.globals.termKey.LEFT:
					sendStrTemp="27,91,68";
					break;
				case Terminal.prototype.globals.termKey.RIGHT:
					sendStrTemp="27,91,67";
					break;
				case Terminal.prototype.globals.termKey.UP:
					sendStrTemp="27,91,65";
					break;
				case Terminal.prototype.globals.termKey.DOWN:
					sendStrTemp="27,91,66";
					break;
				case Terminal.prototype.globals.termKey.BS:
					sendStrTemp="8";
					break;
				case Terminal.prototype.globals.termKey.DEL:
					sendStrTemp="127";
					break;
				case KeyEventDetail.prototype.specialKeysSupported.CTRLZ:
					sendStrTemp="26";
					break;
				case KeyEventDetail.prototype.specialKeysSupported.CTRLV:
					sendStrTemp="22";
					break;
				default:
					;
			}
		}
		return sendStrTemp;
	};
	this.preResponText=function(respText,term){
		if(this.isSpecial&&this.isSupport){
			var flag=this.inputchar;
			switch (flag){
				case Terminal.prototype.globals.termKey.CR:
					break;
				case Terminal.prototype.globals.termKey.LEFT:
					break;
				case Terminal.prototype.globals.termKey.RIGHT:
					break;
				case Terminal.prototype.globals.termKey.UP:
					break;
				case Terminal.prototype.globals.termKey.DOWN:
					break;
				case Terminal.prototype.globals.termKey.BS:
					break;
				case Terminal.prototype.globals.termKey.DEL:
					break;
				case KeyEventDetail.prototype.specialKeysSupported.CTRLZ:
					break;
				case KeyEventDetail.prototype.specialKeysSupported.CTRLV:
					break;
				default:
					;
			}
		}
		return respText;
	};
}

KeyEventDetail.prototype={

    specialKeysSupported:{
		'CR': Terminal.prototype.globals.termKey.CR,
		'LEFT': Terminal.prototype.globals.termKey.LEFT,
		'RIGHT': Terminal.prototype.globals.termKey.RIGHT,
		'UP': Terminal.prototype.globals.termKey.UP,
		'DOWN': Terminal.prototype.globals.termKey.DOWN,
		'BS': Terminal.prototype.globals.termKey.BS,
		'DEL': Terminal.prototype.globals.termKey.DEL,
		'CTRLZ': 26,
		'CTRLV': 22
	},
	getNomalDetail:function(charValue){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=charValue;
		return currentEvent;
	},
	getSpeciclDetail:function(charValue){
	    var detail= KeyEventDetail.prototype.getDefaultSpecialDetail(charValue);
		switch (charValue){
				case Terminal.prototype.globals.termKey.CR:
					detail=KeyEventDetail.prototype.getEnterDetail();
					break;
				case Terminal.prototype.globals.termKey.LEFT:
					detail=KeyEventDetail.prototype.getLeftDetail();
					break;
				case Terminal.prototype.globals.termKey.RIGHT:
					detail=KeyEventDetail.prototype.getRightDetail();
					break;
				case Terminal.prototype.globals.termKey.UP:
					detail=KeyEventDetail.prototype.getUpDetail();
					break;
				case Terminal.prototype.globals.termKey.DOWN:
					detail=KeyEventDetail.prototype.getDownDetail();
					break;
				case Terminal.prototype.globals.termKey.BS:
					detail=KeyEventDetail.prototype.getBsDetail();
					break;
				case Terminal.prototype.globals.termKey.DEL:
					detail=KeyEventDetail.prototype.getDelDetail();
					break;
				case KeyEventDetail.prototype.specialKeysSupported.CTRLZ:
					detail=KeyEventDetail.prototype.getCtrlzDetail();
					break;
				case KeyEventDetail.prototype.specialKeysSupported.CTRLV:
					detail=KeyEventDetail.prototype.getCtrlvDetail();
					break;
				default:
					;
		}
		return detail;
	},
	getDefaultSpecialDetail:function(chatValue){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=chatValue;
		currentEvent.isSpecial=true;
		currentEvent.isSupport=false;
		return currentEvent;
	},
	getEnterDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=Terminal.prototype.globals.termKey.CR;
		currentEvent.isSpecial=true;
		return currentEvent;
	},
	getLeftDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=Terminal.prototype.globals.termKey.LEFT;
		currentEvent.isSpecial=true;
		return currentEvent;
	},
	getRightDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=Terminal.prototype.globals.termKey.RIGHT;
		currentEvent.isSpecial=true;
		return currentEvent;
	},
	getUpDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=Terminal.prototype.globals.termKey.UP;
		currentEvent.isSpecial=true;
		return currentEvent;
	},
	getDownDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=Terminal.prototype.globals.termKey.DOWN;
		currentEvent.isSpecial=true;
		return currentEvent;
	},
	getBsDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=Terminal.prototype.globals.termKey.BS;
		currentEvent.isSpecial=true;
		return currentEvent;
	},
	getDelDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=Terminal.prototype.globals.termKey.DEL;
		currentEvent.isSpecial=true;
		return currentEvent;
	},
	getCtrlzDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=KeyEventDetail.prototype.specialKeysSupported.CTRLZ;
		currentEvent.isSpecial=true;
		return currentEvent;
	},
	getCtrlvDetail:function(){
		var currentEvent=new KeyEventDetail();
		currentEvent.inputchar=KeyEventDetail.prototype.specialKeysSupported.CTRLZ;
		currentEvent.isSpecial=true;
		return currentEvent;
	}

	
}

function HelperUtil(){
}
HelperUtil.prototype={

	removeCharbyDelIndex:function(text){
	         return text;
	}
	
}