let btn = document.querySelectorAll("button");let turns = 0;let arx =[],aro =[];
let win_pattern =[
    [0, 1, 2], [3, 4, 5], [6, 7, 8],
    [0, 3, 6], [1, 4, 7], [2, 5, 8],
    [0, 4, 8], [2, 4, 6]
]
btn.forEach((b,i)=>{
b.addEventListener("click",()=>{
if((turns%2)==0)
    {
    b.innerText="X";
    turns++;
    arx.push(i);
}    
else{
    b.innerText="O";
    turns++;
    aro.push(i);
    console.log(aro);
}
b.disabled = true;
const wono = win_pattern.some(combo=>combo.every(index=>aro.includes(index)));
const wonx = win_pattern.some(combo=>combo.every(index=>arx.includes(index)));
if (wono){alert("PLAYER O WON");
//code later for resetting    


}
if (wonx){alert("PLAYER X WON");
    //code here for resetting
}

})
});