// Function to fetch and update the current pump status
async function fetchPumpStatus() {
    const response = await fetch("{% url 'get_pump_status' %}");
    const data = await response.json();
    updatePumpStatusIndicator(data.is_pump_on);
}

// Function to fetch sensor data and update charts
async function fetchDataAndUpdateCharts() {
    const response = await fetch("{% url 'get_latest_sensor_data' %}");
    const data = await response.json();

    // Update each chart with new data
    updateCharts(data);
}

// Fetch data every 5 seconds
setInterval(fetchDataAndUpdateCharts, 5000);

// Fetch initial pump status on page load
fetchPumpStatus();
