    //********************************************************************************//
    //* Name :  Egor Dourasov                                                        *//
    //* zenit login : int222_161_b08                                                 *//
    //********************************************************************************//
    //********************************************************************************//
    //*   Do not modify any statements in detailPaymentCalculation function          *//
    //********************************************************************************//

//global variable - Collection of Error Messages
var messages = "";
	
function detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization) {

    //********************************************************************************//
    //*   This function calculates the monthly payment based on the following:       *//
    //*                                                                              *//
    //*               M = P [ i(1 + i)n ] / [ (1 +  i)n - 1]                         *//
    //*                                                                              *//
    //*   Note: This function also updates the payment amount on the form            *//
    //********************************************************************************//
     var paymentError = "";
     var v = mortAmount * 1;
     var d = mortDownPayment * 1;
     var i = mortRate * 1;
     var y = mortAmortization * 1;
     var a = v - d;
         i = i/100/12;
         n = y * 12;
     var f = Math.pow((1+i),n);

     var p = (a * ((i*f)/(f-1))).toFixed(2);

     if (p=="NaN" || p=="Infinity") {
         document.forms[0].payment.value = "";
     }
     else {
           document.forms[0].payment.value = p;
     }

} // End of detailPaymentCalculation function


function calculatePayment() {   
	messages = "";
	//assign initial states
	var valid = true;
	
	
	//call value validation functions and assign their states to variables

	var chkDownPay= checkDownPay();
	var chkPropVal = checkPropValue();
	var chkIntRate = checkIntRate();
	var chkAmor = checkAmortization();

	//check if any states are false
	if (chkDownPay === false) {valid = false;}
	if (chkIntRate === false) {valid = false;}
	if (chkAmor === false) {valid = false;}
	if (chkPropVal === false) {valid = false;}
	
	//if the states are true Calculate the payment and call form validation
	if (valid === true){
		var mortAmount = document.mortgage.propValue.value;
		var mortDownPayment = document.mortgage.downPay.value;
		var mortRate = document.mortgage.intRate.value;
		var mortAmortization = document.mortgage.amortization.value;
		detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization);  

	}
	else {
		messages += "<p>Please enter proper financial information and then click on Calculate Monthly Payment</p>";
	}	
	
	
	showErrors(messages);
	
	return valid;
} // End of calculatePayment function


//prints all of the error messages
function showErrors(messages) {
        
         document.getElementById('errors').innerHTML = messages;

     }  //  End of function

//collection of validation calls	 
function formValidation() {
	messages = "";
    var valid = calculatePayment();

	//call validation functions and assign their returns to variables
	
		var chkIncome = checkIncome();
		var chkPropLoc = checkPropLocation();
		var chkPropType = checkPropDetails();
		var chkClient = checkClient();
		var chkID = checkID();
		var chkMortYear = checkMortYear();
		var chkMortMonth = checkMortMonth();
	
		//check for any false returns
		if (chkIncome === false) {valid = false;}
		if (chkPropLoc === false) {valid = false;}
		if (chkPropType === false) {valid = false;}
		if (chkClient === false) {valid = false;}
		if (chkID === false) {valid = false;}
		if (chkMortYear === false) {valid = false;}
		if (chkMortMonth === false) {valid = false;}
	
	
	
	if (valid === true){
		calculatePayment();
	
		var name = document.mortgage.client.value.split(""); 
		name[0]=name[0].toUpperCase();
		name = name.join("");
		document.mortgage.client.value = name;
		
		document.mortgage.jsActive.value = "Y";
		
	}

	showErrors(messages);
	return valid;

} // End of completeFormValidation


//Cheks whether income is selected
 function checkIncome() {
               
               var index = document.mortgage.income.selectedIndex;
                                                         
               if (index === -1) {                                        
                    messages += "<p>Income not selected</p>"; 
                    return false; 
				}
               else {   
					return true; 					
               }
               
    } // End of function
function checkPropLocation() {
               
               var index = document.mortgage.propLocation.selectedIndex;
                                                         
               if (index === -1) {                                        
                    messages += "<p>Property Location not selected</p>"; 
                    return false; 
				}
               else {   
					return true; 					
               }
               
    } // End of function
	
// validates that a property type radial is selected
function checkPropDetails(){
	var num = document.mortgage.propDetails.length;
	var valid = false;
	for (var i = 0; i < num; i++){
		if (document.mortgage.propDetails[i].checked){
			valid = true;
		}
	}
	if (valid === false){
		messages += "<p>Property Type is not selected</p>";
	}
	return valid;
}


/*
Validates Client Name
Must have at least 3 alphabetic characters (a-z) (A-Z) at the beginning of the field
an apostrophe (') at the beginning or at the end of the name is not valid
*/
function checkClient(){
	var valid = true;
	var name = document.mortgage.client.value;
	var chari;
	//loop for checking characters in the name
	var count = false;
	var apos = 1;
	var apos_be = false;
	for (var i = 0; i < name.length; i++){
		chari = name.charCodeAt(i);
		//check if characters are alphabetic or an apostrophe (')
		if (chari === 39 || (chari>64 && chari<91) || (chari>95 && chari<123)){
			//checks if there is an apostrophe at the beginning or end of the name
			if (chari === 39) {
				apos += 1;
			}
			if ((i === 0 || i === (name.length-1)) && chari == 39) {
				apos_be = true;
			}
			
		} else{
			valid = false;
			count = true;
			
		}
	} 
		if (count === true){
		messages += "<p>Client Name must consist of Alphabetic Characters</p>";
	}
	if (valid === true && apos_be === true){
		valid = false;
		messages += "<p>Client Name may not start or end with an apostrophe (') </p>";
	}
	//checks if the name is at least 3 characters long
	if (valid === true && apos > 2){
		valid = false;
		messages += "<p>Client Name may not have more than one apostrophe (') </p>";
	}
	if (valid === true && name.length < 3){
		messages += "<p>Client Name should be at least 3 characters long</p>";
		valid = false;
	}
	return valid;
}

/*
Property Value Validation
Must be present
Must be numeric - positive - whole number
Must be at least 65,000 dollars more that the down payment.
*/
function checkPropValue(){
	var val = document.mortgage.propValue.value;
	var valid = true;
	var chari;
	//Must be present
	
	if (val.length === 0){
		messages += "<p>Please Enter a Property Value</p>";
		valid = false;
	}
	//Must be numeric - positive - whole number
	var count = false;
	for (var i = 0; i < val.length; i++){
		chari = val.charCodeAt(i);
		if (chari>47 && chari<58){
			val;
		}
		else {
			valid = false;
			count = true;
		}
	}
	if (count === true){
		messages += "<p>Property value should be a +ve whole number - no decimals or commas</p>";
	}
	//Must be at least 65,000 dollars more that the down payment.
	var dif = val - document.mortgage.downPay.value;
	if (valid === true && dif <65000){
		messages += "<p>Property value must be at least 65,000 dollars more that the down payment.</p>";
		valid = false;
	}
	return valid;
}


/*
Must be present
Must be numeric - positive - whole number
Must be at least 20% of the value of the property (propValue)
*/
function checkDownPay(){
	var val = document.mortgage.downPay.value;
	var valid = true;
	var chari;
	//Must be present
	
	if (val.length === 0){
		messages += "<p>Please Enter a Down Payment</p>";
		valid = false;
	}
	//Must be numeric - positive - whole number
	var count = false;
	for (var i = 0; i < val.length; i++){
		chari = val.charCodeAt(i);
		if (chari>47 && chari<58){
			val;
		}
		else {
			valid = false;
			count = true;
		}
	}
	if (count === true){
		messages += "<p>Down Payment should be a +ve whole number - no decimals or commas</p>";
	}
	//Must be at least 20% of the value of the property (propValue)
	if (valid === true && val < (document.mortgage.propValue.value * 0.2)){
		messages += "<p>Must be at least 20% of the value of the property</p>";
		valid = false;
	}
	return valid;
}

/*
Validates Interest Rate
Must be present
Must be numeric. Allowable values: 3.000 thru 16.000 inclusive
*/
function checkIntRate(){
	var val = document.mortgage.intRate.value;
	var valid = true;
	//Must be present
	if (val.length === 0){
		messages += "<p>Please Enter an Interest Rate</p>";
		valid = false;
	}
	//Must be numeric. Allowable values: 3.000 thru 16.000 inclusive
	if (valid === true && !(val >=3.0 && val <= 16.0)){
		messages += "<p>Interest Rate Must be numeric and between 3 and 16 percent.</p>";
		valid = false;
	}
	return valid;
}

/*
Validates Amortization
Must be present
Must be numeric. Allowable values: 05 thru 20 inclusive
*/
function checkAmortization(){
	var val = document.mortgage.amortization.value;
	var valid = true;
	//Must be present
	if (val.length === 0){
		messages += "<p>Please Enter the Amortization period in years</p>";
		valid = false;
	}
	//Must be numeric. Allowable values: 05 thru 20 inclusive
	if (valid === true && !(val >=5 && val <= 20)){
		messages += "<p>Amortization Must be numeric and between 5 and 20 years</p>";
	}
	return valid;
}


/*
Validate userID
Rule #1	All 10 positions must be present
Rule #2	Position 5 must be a hyphen (-)
Rule #3	Position 1 to 4 must be numeric digits
Rule #4	Position 6 to 10 must be numeric digits
The following two rules (#5 and #6) should only be checked if rule 1 through rule 4 has passed the validation
Rule #5	The sum of the numbers to the left of the hyphen (-) must be greater than zero and the sum of the numbers to the right of the hyphen (-) must be greater than zero
Rule #6	The sum of the numbers to the right of the hyphen (-) must be (double plus 2) the sum of the numbers to the left of the hyphen (-)
You must provide a different message for the different error conditions
*/
function checkID(){
	var val = document.mortgage.userId.value;
	var valid = true;
	var chari;
	//Rule #1	All 10 positions must be present
	if (val.length < 10){
		messages += "<p>User ID is supposed to be 10 characters long</p>";
		valid = false;
	}
	//Rule #2	Position 5 must be a hyphen (-)
	if (valid === true && (val.charCodeAt(4) != 45)){
		messages += "<p>Position 5 of the User ID must be a hyphen (-)</p>";
		valid = false;
	}
	var count = false;
	//Rule #3	Position 1 to 4 must be numeric digits
	//Rule #4	Position 6 to 10 must be numeric digits
	for (var i = 0; i < 10; i++){
		chari = val.charCodeAt(i);
		if (i === 4){
			val;
		}
		else if (valid === true && (chari>47 && chari<58)){
			val;
		}
		else {
			count = true;
			break;
		}
	}
	if (valid === true && count === true){
		messages += "<p>Position 1-4 and 6-10 of the User ID must be numeric</p>";
		valid = false;
	}
	if (valid === true){
		var left = 0;
		var right = 0;
		for (i = 0; i < 4; i++){
			left += val.charAt(i)*1;
		}
		for (i = 5; i < 10; i++){
			right += val.charAt(i)*1;
		}
		//Rule #5	The sum of the numbers to the left of the hyphen (-) must be greater than zero and the sum of the numbers to the right of the hyphen (-) must be greater than zero
		if (left <= 0 || right <= 0){
			messages += "<p>The sum of the numbers to the left of the hyphen (-) must be greater than zero and the sum of the numbers to the right of the hyphen (-) must be greater than zero</p>";
			valid = false;
		}
		var dif =  (right) - (left*2 + 2);
		//Rule #6	The sum of the numbers to the right of the hyphen (-) must be (double plus 2) the sum of the numbers to the left of the hyphen (-)
		if (valid === true && dif !== 0){
			messages += "<p>The sum of the numbers to the right of the hyphen (-) must be (double plus 2) the sum of the numbers to the left of the hyphen (-)</p>";
			valid = false;
		}
	}
	
	
	return valid;
}

/* Validate Mortgage Year
Must be present
Must be numeric
Must be equal to the current year or 1 year greater than current year.
*/
function checkMortYear(){
	var val = document.mortgage.mortYear.value;
	var valid = true;
	var chari;
	var count;
	var myDate = new Date();
	var myYear = myDate.getFullYear();
	//Must be present
	if (val.length === 0){
		messages += "<p>Please Enter the Mortgage Year</p>";
		valid = false;
	}
	//Must be numeric
	for (var i = 0; i < val.length; i++){
		chari = val.charCodeAt(i);
		if (valid === true && (chari>47 && chari<58)){
			val;
		}
		else {
			count = true;
			break;
		}
	}
	if (valid === true && count === true){
		messages += "<p>Mortgage Year must be a numeric value</p>";
		valid = false;
	}
	//Must be equal to the current year or 1 year greater than current year.
	if (valid === true && !(val == myYear || val == (myYear+1))){
		messages += "<p>Mortgage Year Must be equal to the current year or 1 year greater than current year.</p>";
		valid = false;
	}
	return valid;
}

/* Validate Mortgage Month
Must be present
Must be numeric.
Must be equal to the current month or 1 month greater than current month.
Allowable values: 01 thru 12 inclusive
*/

function checkMortMonth(){
	var val = document.mortgage.mortMonth.value;
	var valid = true;
	var chari;
	var count;
	var myDate = new Date();
	var myMonth = myDate.getMonth();
	//Must be present
	if (val.length === 0){
		messages += "<p>Please Enter the Mortgage Month</p>";
		valid = false;
	}
	//Must be numeric
	for (var i = 0; i < val.length; i++){
		chari = val.charCodeAt(i);
		if (valid === true && (chari>47 && chari<58)){
			val;
		}
		else {
			count = true;
			break;
		}
	}
	if (valid === true && count === true){
		messages += "<p>Mortgage Month must be a numeric value</p>";
		valid = false;
	}
	//Allowable values: 01 thru 12 inclusive
	if (valid === true && !(val >=1 && val <=12)){
		messages += "<p>Mortgage Month must be between 1 and 12 inclusive</p>";
		valid = false;
	}
	//Must be equal to the current month or 1 month greater than current month.
	if (valid === true && !(val == myMonth+1 || val == (myMonth+2))){
		messages += "<p>Mortgage Month be equal to the current month or 1 month greater than current month</p>";
		valid = false;
	}
	return valid;
}


