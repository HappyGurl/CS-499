CS-499 5-2 Module Five
Serrina Paasch
Southern New Hampshire University
CS-499 Computer Science Capstone 2024
Brooke Goggin
September 27th, 2024

Briefly describe the artifact. What is it? When was it created?

  The artifact I created is an interactive dashboard developed for Grazioso Salvare, a rescue animal training company, as part of my CS-340 project in 2024. The purpose of this dashboard is to provide a user-friendly platform for filtering and organizing data related to rescue animals. Key features include interactive visualizations using Python's Plotly and Folium libraries, which allow users to view animal information on a map, aiding in identifying patterns and trends across different locations. Furthermore, I incorporated machine learning techniques, such as k-means clustering via scikit-learn, to classify animals based on characteristics like breed, age, and training potential. This feature enhances decision-making in identifying suitable candidates for search-and-rescue training. The project leverages MongoDB as a NoSQL database to store and retrieve animal records, emphasizing my ability to manage large datasets effectively. This artifact showcases my technical skills in integrating data visualization, machine learning, and backend technologies into practical applications, while also demonstrating my ability to build cohesive solutions that help organizations like Grazioso Salvare improve their processes and outcomes.

  
Justify the inclusion of the artifact in your ePortfolio. Why did you select this item? What specific components of the artifact showcase your skills and abilities in software development? How was the artifact improved?

  I  selected this interactive dashboard for my ePortfolio because it exemplifies my ability to integrate multiple technical components—data visualization, machine learning, and software development—into a cohesive and functional application. This artifact showcases my skills in developing user-centric solutions by enabling users to filter data using MongoDB queries, visualize rescue animal information on a map using Folium, and apply machine learning techniques, like k-means clustering in scikit-learn, to classify animals. These components illustrate my proficiency in both front-end and back-end development, as well as data analysis, to solve real-world problems.
The artifact was significantly improved through the addition of machine learning capabilities, which automated the classification process for rescue animal candidates, providing insights without manual data analysis. I also enhanced the user interface with Bootstrap to make data filtering more intuitive, ensuring that the dashboard is functional and visually appealing. Additionally, I refactored the codebase by modularizing the components into separate Python scripts for different functionalities (e.g., data extraction, clustering, and visualization), improving the maintainability and scalability of the project. This artifact illustrates my growth in software development, my adaptability, and my focus on delivering professional-quality work.


Did you meet the course outcomes you planned to meet with this enhancement in Module One? Do you have any updates to your outcome-coverage plans?

  I modularized the code into distinct components like animal_shelter.py. This modularity supports easier collaboration, as different team members can work on separate aspects of the project independently, improving overall maintainability and reducing coupling between components.
  The dashboard's professional-quality communications are demonstrated through a clean, user-friendly interface built with Bootstrap, which allows users to navigate through different features seamlessly. Interactive elements like tooltips, filtering forms, and map markers ensure that data presentations are clear and accessible to users with varying technical backgrounds.
  By integrating machine learning techniques like k-means clustering, I demonstrated my ability to design sophisticated computing solutions that address real-world problems, such as rescue animal classification. The use of sci-kit-learn allowed for efficient clustering and made the classification process more effective.
  One notable improvement was transitioning from hardcoded credentials to environment variables, which significantly enhanced the security and flexibility of the application. By storing sensitive information, such as MongoDB credentials, in environment variables, I ensured that these values are not exposed directly in the codebase. This change aligns with best practices for secure and maintainable software development and facilitates easier deployment across different environments.

  
Reflect on the process of enhancing and modifying the artifact. What did you learn as you were creating it and improving it? What challenges did you face?

  During the enhancement process, I gained a deeper understanding of interactive data visualization and the challenges involved in integrating machine learning into web applications. One significant challenge was ensuring the k-means clustering results were meaningful, which required extensive data preprocessing and careful selection of features. I experimented with various combinations of features to identify the ones that provided the most accurate and insightful clustering. Another challenge was optimizing the user interface to ensure that the dashboard was visually appealing and intuitive. I learned how to balance functionality with user experience, using Bootstrap and JavaScript to create a responsive and interactive interface.

Course outcomes that have been met so far: 
Employ strategies for building collaborative environments that enable diverse audiences to support organizational decision-making in the field of computer science.  
Design, develop, and deliver professional-quality oral, written, and visual communications that are coherent, technically sound, and appropriately adapted to specific audiences and contexts.  
Design and evaluate computing solutions that solve a given problem using algorithmic principles and computer science practices and standards appropriate to its solution while managing the trade-offs involved in design choices.  
Demonstrate an ability to use well-founded and innovative techniques, skills, and tools in computing practices to implement computer solutions that deliver value and accomplish industry-specific goals.
Develop a security mindset that anticipates adversarial exploits in software architecture and designs to expose potential vulnerabilities, mitigate design flaws, and ensure privacy and enhanced security of data and resources.
