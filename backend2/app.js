import express from 'express'

const app = express()

const PORT = 5002

app.use(express.json())

app.get('/', (req,res)=>{
    // Add a 5 second delay to simulate heavy processing
    setTimeout(() => {
        res.send("Response from Backend2");
    }, 5000);
})


app.get("/about", (req, res) => {
  res.send("About Page from Backend Server 2");
});

app.get("/health", (req, res) => {
  res.status(200).json({
    status: "healthy",
    server: "Backend Server 2",
  });
});

app.listen(PORT, () => {
  console.log(`Backend Server 2 running on port ${PORT}`);
});




