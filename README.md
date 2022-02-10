# WebC-Interaction-Lib
For if you want to code in C++, and need to do simple things such as:<br>
* Accessing(r/w) the HTML dom<br>
* Accissing localStorage for persistent storage<br>

please note before using:  Even though this is webassembly, you won't gain any proformance(and may even lose some) as the only way to currently access the DOM is through javascript calls so this is effectively a wrapper over js.
