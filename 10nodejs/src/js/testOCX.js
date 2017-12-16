require('winax');

(function(){
  try{
    var testOCX = new ActiveXObject("TESTOCX.TestOCXCtrl.1");
    //向ocx中注册一个callback，ocx那边立即执行callback
    testOCX.TestCallback('numsg', callback);
    //调用ocx中的test方法
    var result = testOCX.test(1, 2);
    console.log(result);
  } catch(ex){
    console.log(ex.message);
  }

  function callback(strNum){
    console.log("this is callback, ocx exec function success, ret= " + strNum);
  }
  
})()

