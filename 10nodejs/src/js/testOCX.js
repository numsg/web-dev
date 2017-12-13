require('winax');
var testOCX = new ActiveXObject("TESTOCX.TestOCXCtrl.1");
var result = 'ok';
try{
  console.dir(testOCX);
  var result = testOCX.test(1,2);
  console.log(result);
} catch(ex){
  result = ex.message;
  console.log(result);
  console.log(ex.stack);
}
