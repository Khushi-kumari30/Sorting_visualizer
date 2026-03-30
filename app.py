import streamlit as st
import subprocess
import time

st.title("Sorting Visualizer")

# The data is still here, but we won't show it immediately
complexity_map = {
    "Bubble": {"Best": "O(n)", "Worst": "O(n²)", "Space": "O(1)"},
    "Selection": {"Best": "O(n²)", "Worst": "O(n²)", "Space": "O(1)"},
    "Insertion": {"Best": "O(n)", "Worst": "O(n²)", "Space": "O(1)"},
    "Quick": {"Best": "O(n log n)", "Worst": "O(n²)", "Space": "O(log n)"},
    "Merge": {"Best": "O(n log n)", "Worst": "O(n log n)", "Space": "O(n)"}
}

selected_algo = st.selectbox("Pick an Algorithm", list(complexity_map.keys()))

user_input = st.text_input("Enter numbers separated by spaces", "10 5 2 8 7 1")
numbers = user_input.split()

# Create a place for metrics and chart BEFORE the button click logic
metrics_placeholder = st.empty()
chart_placeholder = st.empty()

if st.button("Start Sorting"):
    # 1. NOW show the complexity metrics since the user started
    with metrics_placeholder.container():
        col1, col2, col3 = st.columns(3)
        col1.metric("Best Case", complexity_map[selected_algo]["Best"])
        col2.metric("Worst Case", complexity_map[selected_algo]["Worst"])
        col3.metric("Space", complexity_map[selected_algo]["Space"])
        st.markdown("---")

    # 2. Run the C++ process
    cmd = ["./sort_engine", selected_algo] + numbers
    
    process = subprocess.Popen(
        cmd, 
        stdout=subprocess.PIPE, 
        text=True, 
        bufsize=1 
    )

    for line in iter(process.stdout.readline, ""):
        if line.strip():
            current_state = [int(x) for x in line.strip().split(",")]
            chart_placeholder.bar_chart(current_state)
            time.sleep(0.2)
  
    process.stdout.close()
    process.wait()
    st.success(f"{selected_algo} Sorting Complete!")