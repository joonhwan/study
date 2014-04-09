// -*- coding:utf-8; -*-
var variable = "top-level";

function pp(msg) {
	if (typeof window.console != 'undefined') {
		console.log(msg);
	}
}

pp('---------------------------------------------------');

function printVariable() {
	pp("inside printVariable, the variable holds '" +
           variable + "'.");
}

function test() {
	var variable = "local";
	pp("inside test, the variable holds '" + variable + "'.");
	printVariable();
}

test();


var variable = "top-level";
function parentFunction() {
	var variable = "local";
	function childFunction() {
		pp(variable);
	}
	childFunction();
}
parentFunction();


function makeFunc() {
	var variable = "makeFunc variable";
	return function () {
		pp(variable);
	}
}
f = makeFunc();
pp("now calling..");
f(variable);


pp("----");

function makeAddFunction(amount) {
	return function add (number) {
		return number + amount;
	}
	return add;
}

var addTwo = makeAddFunction(2);
var addFive = makeAddFunction(5);

pp("addTwo(2) = " + addTwo(2));
pp("addFive(2)= " + addFive(2));

pp("----");

function findSequence(goal) {
  function find(start, history) {
    if (start == goal)
      return history;
    else if (start > goal)
      return null;
    else
      return find(start + 5, "(" + history + " + 5)") ||
             find(start * 3, "(" + history + " * 3)");
  }
  return find(1, "1");
}

console.log(findSequence(24));
