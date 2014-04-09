// -*- coding:utf-8; -*-

function pp(msg) {
	if (typeof window.console != 'undefined') {
		console.log(msg);
	}
}
var show = pp;

pp('0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-');

function test1() {
	/*
	 속성접근 방식 : 숫자/공백으로 로 시작되지 않으면 된단다.
	 */
	var text = "purple haze"; 		// 문자열 객체
	show("by index : " + text["length"]);
	show("by property: " + text.length);

	/*
	 console창에 오류메시지가 ..
	 */

	// var nothing = null;
	// show(nothing.length);

	// - 문자열의 속성은 변경 불가.
	// - 문자열 속성의 추가/삭제불가. 사전에 정해짐.
	//  --> 하지만 사용자 정의형은 다름.
	var cat = {
		color:"grey",
		name:"Spot",
		size:46
	};
	cat.size = 47;
	show(cat.size);
	// delete cat.size;
	// show(cat.size);
	show(cat);

	var empty  = {};
	empty.notReally =1000;
	show(empty.notReally);

}
// test1();

function test2() {
	var thing = {
		"gabba gabba": "hey",
		"5":10
	};
	show(thing["5"]);
	thing["5"] = 20;
	show(thing[2+3]); // 어어, 문자열 "5" 속성 값이 반환되네!

	var chineseBox = {};
	chineseBox.content = chineseBox;
	chineseBox.title = "chinese box";
	show("content" in chineseBox);
	show("content" in chineseBox.content);
	show(chineseBox);
}
// test2();

// js 에서 문자열은 모두 immutable.

// js 에서 객체를 가리키는 변수는 모두 참조변수.
function test3() {
	var object1 = {value: 10};
	var object2 = object1;
	var object3 = {value: 10};

	// 실제 생성된 메모리상의 객체는 2개 뿐.
	// 이거 중요. object1-object2 는 모두 동일한 객체를 가리킴.

	// == 연산자는 "동일"객체를 가리키는 지 여부를 확인.(값이 같은게 아님)
	//  서로 같은 값을 가지는 다른 객체의 경우에는 false.
	show(object1 == object2);
	show(object1 == object3);

	object1.value = 15;
	show(object2.value);
	show(object3.value);
}
// test3();

function test4() {

	var mailArchive = {
		0: "안녕하세요 반갑습니다.",
		1: "또 뵙는군요.", 
		2: "지난번에는 잘 들어가셨는지요."
	};
	for(var i=0; i in mailArchive; ++i) {
		show("processing email #"+  i +  ": " + mailArchive[i]);
	}
}
// test4();

function test5() {
	var mailArchive = [
		"안녕하세요 반갑습니다.",
		"또 뵙는군요.", 
		"지난번에는 잘 들어가셨는지요."
	];
	for(var i=0; i<mailArchive.length; ++i) {
		show("processing email #"+  i +  ": " + mailArchive[i]);
	}

	function range(num) {
		var numArray = [];
		for(var i=0; i<=num; ++i) {
			// numArray[i] = i;
			numArray.push(i);
		}
		return numArray;
	}
	show("Ex 4.2 answer = " + range(12));
}
// test5();

function test6() {
	var doh = "Doh";
	show(typeof doh.toUpperCase);
	show(doh.toUpperCase());
}
// test6();


function test7() {
	var words = "Hello Sally Seoyeon"; // "안녕하세요 이서연 양";
	show(words.split(" "));
}
test7();





