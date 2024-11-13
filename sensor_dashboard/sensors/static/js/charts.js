const chartOptions = {
    maintainAspectRatio: false,
    responsive: true,
    scales: {
        x: { ticks: { maxTicksLimit: 5, font: { size: 10 } } },
        y: { ticks: { font: { size: 10 } } }
    },
    plugins: {
        legend: { labels: { font: { size: 10 } } }
    }
};

// Initialize charts
const temperatureChart = new Chart(document.getElementById('temperatureChart').getContext('2d'), {
    type: 'line',
    data: { labels: [], datasets: [{ label: 'Temperature (°C)', backgroundColor: 'rgba(255, 99, 132, 0.2)', borderColor: 'rgba(255, 99, 132, 1)', data: [], borderWidth: 1 }] },
    options: chartOptions
});

// Repeat similar setup for other charts
// ...

// Function to update charts with new data
function updateCharts(data) {
    temperatureChart.data.labels = data.timestamps;
    temperatureChart.data.datasets[0].data = data.temperature;
    temperatureChart.update();

    // Update other charts in a similar manner
}
