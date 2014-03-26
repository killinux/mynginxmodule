var term;
var help = [];
function termOpen()
{
  if ((!term) || (term.closed))
  {
    term = new Terminal(
    {
	  cols:100,
	  rows:36,
      x: 220,
      y: 70,
	  blinkDelay:1000,
	  crsrBlinkMode:true,
	  ps:'',
      termDiv: 'termDiv',
      bgColor: '#232e45',
      greeting: help.join('\n'),
      handler: termHandler,
      exitHandler: myExitHandler
    }
    );
	customTerm(term);
    term.open();
	term.currentEvent=KeyEventDetail.prototype.getNomalDetail(10000);
	term.handler();
  }
}

function customTerm(term){
   Terminal.prototype.globals.keyHandler=function(e) {
		var tg=Terminal.prototype.globals;
		var term=tg.activeTerm;
		if (tg.keylock || term.lock || term.isMac && e && e.metaKey) return true;
		if (window.event) {
			if (window.event.preventDefault) window.event.preventDefault();
			if (window.event.stopPropagation) window.event.stopPropagation();
		}
		else if (e) {
			if (e.preventDefault) e.preventDefault();
			if (e.stopPropagation) e.stopPropagation();
		}
		var ch;
		var ctrl=false;
		var shft=false;
		var remapped=false;
		var termKey=term.termKey;
		var keyRepeat=0;
		if (e) {
			ch=e.which;
			ctrl=((e.ctrlKey && !e.altKey) || e.modifiers==2);
			shft=(e.shiftKey || e.modifiers==4);
			if (e._remapped) {
				remapped=true;
				if (window.event) {
					//ctrl=(ctrl || window.event.ctrlKey);
					ctrl=(ctrl || (window.event.ctrlKey && !window.event.altKey));
					shft=(shft || window.event.shiftKey);
				}
			}
			if (e._repeated) {
				keyRepeat=2;
			}
			else if (e._repeat) {
				keyRepeat=1;
			}
		}
		else if (window.event) {
			ch=window.event.keyCode;
			//ctrl=(window.event.ctrlKey);
			ctrl=(window.event.ctrlKey && !window.event.altKey); // allow alt gr == ctrl alt
			shft=(window.event.shiftKey);
			if (window.event._repeated) {
				keyRepeat=2;
			}
			else if (window.event._repeat) {
				keyRepeat=1;
			}
		}
		else {
			return true;
		}
		if (ch=='' && remapped==false) {
			// map specials
			if (e==null) e=window.event;
			if (e.charCode==0 && e.keyCode) {
				if (e.DOM_VK_UP) {
					var dkr=tg.termDomKeyRef;
					for (var i in dkr) {
						if (e[i] && e.keyCode == e[i]) {
							ch=dkr[i];
							break;
						}
					}
				}
				else {
					// NS4
					if (e.keyCode==28) { ch=termKey.LEFT; }
					else if (e.keyCode==29) { ch=termKey.RIGHT; }
					else if (e.keyCode==30) { ch=termKey.UP; }
					else if (e.keyCode==31) { ch=termKey.DOWN; }
					// Mozilla alike but no DOM support
					else if (e.keyCode==37) { ch=termKey.LEFT; }
					else if (e.keyCode==39) { ch=termKey.RIGHT; }
					else if (e.keyCode==38) { ch=termKey.UP; }
					else if (e.keyCode==40) { ch=termKey.DOWN; }
					// just to have the TAB mapping here too
					else if (e.keyCode==9) { ch=termKey.TAB; }
				}
			}
		}
		// leave on unicode private use area (might be function key etc)
		if ((ch>=0xE000) && (ch<= 0xF8FF)) return;
		if (keyRepeat) {
			tg.clearRepeatTimer();
			tg.keyRepeatTimer = window.setTimeout(
				'Terminal.prototype.globals.doKeyRepeat('+ch+')',
				(keyRepeat==1)? tg.keyRepeatDelay1:tg.keyRepeatDelay2
			);
		}
		if (!ctrl) {
			// special keys
			if (ch==termKey.CR) {//entry*********************************************************************************************************************
				term.lock=true;
				term.cursorOff();
				term.insert=false;
				term.lineBuffer=term._getLine(true);
				if (
					term.lineBuffer!='' &&
					(!term.historyUnique || term.history.length==0 ||
					term.lineBuffer!=term.history[term.history.length-1])
					) {
					term.history[term.history.length]=term.lineBuffer;
				}
				term.histPtr=term.history.length;
				term.lastLine='';
				term.inputChar=0;
				term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(ch);
				term.handler();
				term.lock=false;
				term.cursorOn();
				term.insert=true;
				if (window.event) window.event.cancelBubble=true;
				return false;
			}
			else if (ch==termKey.ESC && term.conf.closeOnESC) {//ESC********************************************************************************
				term.close();
				if (window.event) window.event.cancelBubble=true;
				return false;
			}

			{
				if (ch==termKey.LEFT) {//LEFT*****************************************************************************************************************
					//term.cursorLeft();
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(ch);
					term.handler();
					//no need  if add follow ,curcor move becaome slow
					//term.lock=false;
					//term.cursorOn();
					//term.insert=true;
					if (window.event) window.event.cancelBubble=true;
					return false;
				}
				else if (ch==termKey.RIGHT) {
					//term.cursorRight();
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(ch);
					term.handler();
					if (window.event) window.event.cancelBubble=true;
					return false;
				}
				else if (ch==termKey.UP) {
					term.cursorOff();
					/**
					if (term.histPtr==term.history.length) term.lastLine=term._getLine();
					term._clearLine();
					if (term.history.length && term.histPtr>=0) {
						if (term.histPtr>0) term.histPtr--;
						term.type(term.history[term.histPtr]);
					}
					else if (term.lastLine) {
						term.type(term.lastLine);
					}
					*/
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(ch);
					term.handler();
					term.cursorOn();
					if (window.event) window.event.cancelBubble=true;
					return false;
				}
				else if (ch==termKey.DOWN) {
					term.cursorOff();
					/**
					if (term.histPtr==term.history.length) term.lastLine=term._getLine();
					term._clearLine();
					if (term.history.length && term.histPtr<=term.history.length) {
						if (term.histPtr<term.history.length) term.histPtr++;
						if (term.histPtr<term.history.length) {
							term.type(term.history[term.histPtr]);
						}
						else if (term.lastLine) {
							term.type(term.lastLine);
						}
					}
					else if (term.lastLine) {
						term.type(term.lastLine);
					}
					*/
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(ch);
					term.handler();
					term.cursorOn();
					if (window.event) window.event.cancelBubble=true;
					return false;
				}
				else if (ch==termKey.BS) {
					//term.backspace();
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(ch);
					term.handler();
					if (window.event) window.event.cancelBubble=true;
					return false;
				}
				else if (ch==termKey.DEL) {
					/**
					if (term.DELisBS) {
						term.backspace();
					}
					else {
						term.fwdDelete();
					}
					*/
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(ch);
					term.handler();
					if (window.event) window.event.cancelBubble=true;
					return false;
				}
			}
		}
		
		{
			if (term.conf.catchCtrlH && (ch==termKey.BS || (ctrl && ch==72))) {
				// catch ^H
				//term.backspace();
				term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(0);
				term.handler();
				if (window.event) window.event.cancelBubble=true;
				return false;
			}
			else if (term.ctrlHandler && (ch<32 || (ctrl && term.isPrintable(ch,true)))) {//Ctrl unprintable key **************************************************
				if ((ch>=65 && ch<=96) || ch==63) {
					// remap canonical
					if (ch==63) {
						ch=31;
					}
					else {
						ch-=64;
					}
				}
				term.inputChar=ch;
				//term.ctrlHandler();
				term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(0);
				term.handler();
				if (window.event) window.event.cancelBubble=true;
				return false;
			}
			else if (ctrl || !term.isPrintable(ch,true)) {//Ctrl printable key ************************************************************************************************
				if(ctrl && ch==122||ctrl && ch==90){//Ctrl z
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(26);
				}else if(ctrl && ch==118||ctrl && ch==86){//Ctrl v
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(22);
				}else{
					term.currentEvent=KeyEventDetail.prototype.getSpeciclDetail(0);
				}
				term.handler();
				if (window.event) window.event.cancelBubble=true;
				return false;
			}
			else if (term.isPrintable(ch,true)) {//printable key*****************************************************************************************************************
				if (term.blinkTimer) clearTimeout(term.blinkTimer);
				/**
				if (term.insert) {
					term.cursorOff();
					term._scrollRight(term.r,term.c);
				}
				term._charOut(ch);
				term.cursorOn();
				*/
				if (ch==32 && window.event) {
					window.event.cancelBubble=true;
				}
				else if (window.opera && window.event) {
					window.event.cancelBubble=true;
				}
				term.currentEvent=KeyEventDetail.prototype.getNomalDetail(ch);
				term.handler();
				term.lock=false;
				term.cursorOn();
				term.insert=true;
				return false;
			}
		}
		return true;
   };
}

function termHandler() {
		var keyEvent=this.currentEvent;
		var termpCharCode=0;
		var sendStr="0";
		if(keyEvent){
			termpCharCode=keyEvent.inputchar;
			sendStr=String(termpCharCode);
		}else{
			return;
		}
		if(keyEvent.isSpecial){
			if(keyEvent.isSupport){
				sendStr=keyEvent.getSendCmd();
			}else{
				return ;
			}
		}
		var myDataObject = {
              charCode: sendStr,
              ipaddress: "10.46.60.69"
        };
	    this.send(
        {
          //url: "demoApp/easyCRT.action",
          url: "http://haoning.net/echo?ls%20-l",
          method: 'get',
          callback: myServerCallback,
		  //data: myDataObject
        }
     );
}


function myServerCallback()
{
  var response=this.socket;
  if (response.success)
  {
    var func=null;
    try{
      func=eval(response.responseText);
    }catch (e){
    }
    if (typeof func=='function'){
      try{
        func.apply(this);
      }catch(e){
        this.write('An error occured within the imported function: '+e);
      }
    }else{
	  var respText=response.responseText;
	  var temptg=Terminal.prototype.globals;
	  var tempterm=temptg.activeTerm;
	  var keyEvent=tempterm.currentEvent;
	  if(keyEvent.isSpecial&&keyEvent.isSupport){
			var flag=keyEvent.inputchar;
			switch (flag){
				case Terminal.prototype.globals.termKey.CR:
					break;
				case Terminal.prototype.globals.termKey.LEFT:
					leftkey(tempterm,respText);
					return;
					break;
				case Terminal.prototype.globals.termKey.RIGHT:
					rightkey(tempterm,respText);
					return;
					break;
				case Terminal.prototype.globals.termKey.UP:
					break;
				case Terminal.prototype.globals.termKey.DOWN:
					break;
				case Terminal.prototype.globals.termKey.BS:
					break;
				case KeyEventDetail.prototype.specialKeysSupported.CTRLZ:
					break;
				case KeyEventDetail.prototype.specialKeysSupported.CTRLV:
					break;
				default:
					;
			}
	 }
	  respText=keyEvent.preResponText(respText,tempterm);
	  var text=HelperUtil.prototype.removeCharbyDelIndex(respText);
	  this.write(respText);
    }
  }
  else
  {
    var s='Request failed: ' + response.status + ' ' + response.statusText;
    if (response.errno) s += '\n' + response.errstring;
    this.write(s);
  }
}

function leftkey(tempterm,respText){
	if(respText){
		tempterm.cursorLeft();
	}
}
function rightkey(tempterm,respText){
	if(respText){
		tempterm.cursorRight();
	}
}


function myExitHandler()
{
  var mainPane = (document.getElementById)?
  document.getElementById('mainPane') : document.all.mainPane;
  if (mainPane) mainPane.className = 'lh15';
}
