Pebble.addEventListener('showConfiguration', function(e) {
  // Show config page
//   Pebble.openURL('http://pebbleapp.livehost.fr/watchmywallet/index.php');
  Pebble.openURL('http://pebbleapp.livehost.fr/watchmywallet/index.php');  
});

Pebble.addEventListener("webviewclosed",
  function(e) {
    //Get JSON dictionary
    var configuration = JSON.parse(decodeURIComponent(e.response));
    console.log("Configuration window returned: " + JSON.stringify(configuration));
 
    for (var key in configuration) {
      console.log(configuration[key]);
      
      send2pebble(configuration[key]);
    }
//     //Send to Pebble, persist there
//     Pebble.sendAppMessage(
//       {"KEY_INVERT": configuration.invert},
//       function(e) {
//         console.log("Sending settings data...");
//       },
//       function(e) {
//         console.log("Settings feedback failed!");
//       }
//     );
  }
);

function send2pebble(category) {
  console.log(category);
  //Send to Pebble, persist there
  Pebble.sendAppMessage(
    {"KEY_NEW_CATEGORY": category},
    function(e) {
      console.log("Sending settings data...");
    },
    function(e) {
      console.log("Settings feedback failed!");
    }
  );
}