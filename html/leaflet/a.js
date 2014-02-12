$(document).on('pageinit', '#index', function(){  
    var map = L.map('map');
    
    L.tileLayer('http://{s}.tile.cloudmade.com/BC9A493B41014CAABB98F0471D759707/997/256/{z}/{x}/{y}.png', {
        maxZoom: 16,
        attribution: 'Example made by <a href="http://www.gajotres.net">Gajotres</a>'
    }).addTo(map);
    
    map.on('locationfound', onLocationFound);
    map.on('locationerror', onLocationError);
    
    map.locate({setView: true, maxZoom: 18});    
});

function onLocationFound(e) {
    var radius = e.accuracy / 2;
    
    L.marker(e.latlng).addTo(map)
    .bindPopup("You are within " + radius + " meters from this point").openPopup();
    
    L.circle(e.latlng, radius).addTo(map);
}

function onLocationError(e) {
    alert(e.message);
}