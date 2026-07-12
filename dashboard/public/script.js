const API_BASE = "http://localhost:8080";

// Fetch and update metrics
async function fetchMetrics() {
    try {
        const response = await fetch(`${API_BASE}/metrics`);
        if (!response.ok) return;
        const data = await response.json();
        
        document.getElementById("requests").innerText = data.totalRequests || 0;
        document.getElementById("failed").innerText = data.failedRequests || 0;
        document.getElementById("connections").innerText = data.activeConnections || 0;
    } catch (error) {
        console.error("Error fetching metrics:", error);
    }
}

// Fetch and update backends list
async function fetchBackends() {
    try {
        const response = await fetch(`${API_BASE}/backends`);
        if (!response.ok) return;
        const data = await response.json();
        
        const tbody = document.getElementById("backends-body");
        tbody.innerHTML = ""; // Clear existing rows
        
        data.forEach(backend => {
            const tr = document.createElement("tr");
            
            const statusClass = backend.healthy ? "up" : "down";
            const statusText = backend.healthy ? "UP" : "DOWN";
            
            tr.innerHTML = `
                <td>${backend.id}</td>
                <td>${backend.port}</td>
                <td class="${statusClass}">${statusText}</td>
                <td>${backend.requests}</td>
                <td>${backend.totalHandled || 0}</td>
            `;
            
            tbody.appendChild(tr);
        });
    } catch (error) {
        console.error("Error fetching backends:", error);
    }
}

// Change algorithm
async function setAlgorithm(alg) {
    try {
        const response = await fetch(`${API_BASE}/algorithm/${alg}`);
        if (!response.ok) return;
        const data = await response.json();
        
        if (data.status === "success") {
            const isRoundRobin = alg === "round-robin";
            
            document.getElementById("current-algorithm").innerText = isRoundRobin ? "Round Robin" : "Least Connections";
            
            document.getElementById("btn-round-robin").className = isRoundRobin ? "active" : "";
            document.getElementById("btn-least-connection").className = isRoundRobin ? "" : "active";
        }
    } catch (error) {
        console.error("Error setting algorithm:", error);
    }
}

// Simulate heavy traffic
function simulateLoad() {
    console.log("Simulating 30 concurrent requests...");
    for(let i=0; i<30; i++) {
        // We catch the error because we don't care about the response, 
        // we just want to send the HTTP request to the Load Balancer
        fetch("http://localhost:8080/").catch(e => {}); 
    }
}

// Auto-refresh every second
setInterval(() => {
    fetchMetrics();
    fetchBackends();
}, 1000);

// Initial fetch
fetchMetrics();
fetchBackends();
